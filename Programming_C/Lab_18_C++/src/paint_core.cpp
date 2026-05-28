#include "paint_core.hpp"
#include <algorithm>   // std::min, std::max, std::transform, std::fill
#include <cmath>       // std::abs
#include <stack>       // std::stack

extern std::stack<Canvas> undoStack;

// ========== Вспомогательная функция сохранения (уже готова) ==========
void saveToUndo(const Canvas& canvas) {
    undoStack.push(canvas);
}

// ========== 1. Очистка холста (оценка 3) ==========
void clearCanvas(Canvas& canvas) {
    undoStack.push(canvas);
    for (auto &row : canvas) {
        std::fill(row.begin(), row.end(), sf::Color::White);
    }
}

// ========== 2. Рисование пикселя (оценка 3) ==========
void drawPixel(Canvas& canvas, int x, int y, const sf::Color& color) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        canvas[y][x] = color;
    }
}

// ========== 3. Круглая кисть (оценка 3) ==========
void drawBrush(Canvas& canvas, int x, int y, const sf::Color& color, int radius) {
    undoStack.push(canvas);
    for (int dx = -radius; dx <= radius; dx++) {
        for (int dy = -radius; dy <= radius; dy++) {
            if (dx*dx+dy*dy <= radius*radius) {
                drawPixel(canvas, x+dx, y+dy, color);
            }
        }
    }
}

// ========== 4. Прямоугольник (оценка 3) ==========
void drawRectangle(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color) {
    saveToUndo(canvas);
    int left = std::min(x1, x2);
    int right = std::max(x1, x2);
    int top = std::min(y1, y2);
    int bottom = std::max(y1, y2);

    for (int y = top; y <= bottom; y++) {
        for (int x = left; x <= right; x++) {
            drawPixel(canvas, x, y, color);
        }
    }
}

// ========== 5. Линия (Брезенхем) (оценка 4) ==========
void drawLine(Canvas& canvas, int x1, int y1, int x2, int y2, const sf::Color& color) {
    saveToUndo(canvas);
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        drawPixel(canvas, x1, y1, color);
        if (x1 == x2 && y1 == y2) {
            break;
        }
        int err2 = 2 * err;
        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// ========== 6. Undo (оценка 4) ==========
void undo(Canvas& canvas) {
    if (!undoStack.empty()) {
        canvas = undoStack.top();
        undoStack.pop();
    }
}

// ========== 7. Оттенки серого (оценка 5) ==========
void applyGrayscale(Canvas& canvas) {
    saveToUndo(canvas);
    for (auto& row : canvas) {
        std::transform(row.begin(), row.end(), row.begin(), [](const sf::Color& c) {
            sf::Uint8 gray = static_cast<sf::Uint8>((c.r + c.g + c.b) / 3);
            return sf::Color(gray, gray, gray);
        });
    }
}

// ========== 8. Негатив (оценка 5) ==========
void applyNegative(Canvas& canvas) {
    saveToUndo(canvas);
    for (auto& row : canvas) {
        std::transform(row.begin(), row.end(), row.begin(), [](const sf::Color& c) {
            return sf::Color(255 - c.r, 255 - c.g, 255 - c.b);
        });
    }
}

// ========== 9. Размытие (оценка 5) ==========
void applyBlur(Canvas& canvas) {
    saveToUndo(canvas);
    Canvas original = canvas;
    for (int y = 1; y < HEIGHT - 1; ++y) {
        for (int x = 1; x < WIDTH - 1; ++x) {
            int r = 0, g = 0, b = 0;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    const sf::Color& neighbor = original[y + dy][x + dx];
                    r += neighbor.r;
                    g += neighbor.g;
                    b += neighbor.b;
                }
            }
            canvas[y][x] = sf::Color(static_cast<sf::Uint8>(r / 9), static_cast<sf::Uint8>(g / 9), static_cast<sf::Uint8>(b / 9), original[y][x].a);
        }
    }
}  

// ========== 10. Сохранение картинки (оценка *) ==========
bool saveToFile(const Canvas& canvas, const std::string& filename) {
    sf::Image image;
    image.create(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            image.setPixel(x, y, canvas[y][x]);
        }
    }
    return image.saveToFile(filename);
}

// ========== Вспомогательная отрисовка (уже готова) ==========
void renderToWindow(sf::RenderWindow& window, const Canvas& canvas) {
    static sf::Image image;
    static sf::Texture texture;
    static sf::Sprite sprite;
    
    image.create(WIDTH, HEIGHT);
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            image.setPixel(x, y, canvas[y][x]);
    
    texture.loadFromImage(image);
    texture.setSmooth(false);
    sprite.setTexture(texture);
    sprite.setScale(PIXEL_SIZE, PIXEL_SIZE);
    window.draw(sprite);
}