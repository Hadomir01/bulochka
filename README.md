# *Лабораторная работа № 9*

<details>
<summary> На 3... </summary>

## На оценку 3

1. **git status выводит:**

```git
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md

nothing added to commit but untracked files present (use "git add" to track)
```

мы в основной ветке, коммитов нет, файлов тоже

2. **git log:**

```git
fatal: your current branch 'main' does not have any commits yet
```

так как в папке еще ничего нет...

3. **Создадим файл sort.c**

4. **теперь git status выводит:**

```git
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md
        sort.c

nothing added to commit but untracked files present (use "git add" to track)
```

добавился созданный файл

5. **добавим в stage**

6. **git status теперь:**

```git
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   README.md
        new file:   sort.c
```

7. **закоммитим файл**

тут я вернул назад README.md, чтобы постоянно не добавлять и не коммитить его

8. **git status:**

```git
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md

nothing added to commit but untracked files present (use "git add" to track)
```

9. **добавил комментарий**

```c
void bubbleSort(int arr[], int n) //Это сортировка пузырьком
```

10. **git straus:**

```git
On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   sort.c

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

sort.c теперь измененный файл

11. **добавляем в stage**

12. **git status:**

```git
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   sort.c

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md
```

13. **Снова изменим файл(добавим коммент)**

```c
#include <stdio.h> // Это программа на c
```

14. **Делаем коммит без добавления изменений**

```
[main e81962d] добавил коммент в первую строку
 1 file changed, 1 insertion(+), 1 deletion(-)
 ```

15. **status:**

```git
On branch main
Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   sort.c

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md

no changes added to commit (use "git add" and/or "git commit -a")
```

**log:**

```git
commit e81962d2424da6e7e2cba666df3b2de65b51697a (HEAD -> main)
Author: Hadomir01 <okser0656@gmail.com>
Date:   Mon Dec 1 18:11:11 2025 +0700

    добавил коммент в первую строку
...
```

не забудем, что мы не коммитили последние изменения в sort...

16.17. **а сейчас закоммитим и запушим на удаленку уже с изменениями:**

```
Enumerating objects: 10, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 12 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (9/9), 1.12 KiB | 571.00 KiB/s, done.
Total 9 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), done.
To https://github.com/Hadomir01/bulochka
   b7dd34a..55db97b  main -> main
```

**вот, что вышло**
![alt text](image.png)
почему 8 коммитов? Просто чуть ранее я решил немного поиграться с гитом: посоздавал файлы, папки, поудалаял их.

## Теперь задания с ветками

1.2. **создаем новую ветку...**

проверяем:

```git
* main
  mybranch
```
3. **переходим на новую ветку**

```git
Switched to branch 'mybranch'
```

4. **git status:**
```git
On branch mybranch
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        README.md
        image.png

nothing added to commit but untracked files present (use "git add" to track)
```
в самой первой строке пометка, что мы в ветке 'mybranch'

5. **проверим...**
```git
  main
* mybranch
```

6-7. **создадим файл file1.txt и сохраним изменение**

```git
[mybranch 15d2900] создал файл file1.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 file1.txt
```

8. **git log:**
```git
* 15d2900 (HEAD -> mybranch) создал файл file1.txt
* 55db97b (origin/main, main) теперь точно добавил коммент в первую строку
* c6b06e2 добавил коммент в первую строку
* 9e4d180 Добавили
* b7dd34a (bulochka/main) Delete programming_C directory
* 2dfcd52 Delete Hello_world.c
* d38fba1 Update Hello_world.c
* 521423f hello_world.c
* e20c128 Hello_world.c
```

9-10. **вернулись на ветку main и вот что выдает git log:**
```git
* 55db97b (HEAD -> main, origin/main) теперь точно добавил коммент в первую строку
* c6b06e2 добавил коммент в первую строку
* 9e4d180 Добавили
* b7dd34a (bulochka/main) Delete programming_C directory
* 2dfcd52 Delete Hello_world.c
* d38fba1 Update Hello_world.c
* 521423f hello_world.c
* e20c128 Hello_world.c
```
заметим, что нет последнего коммита, где мы создали file1.txt, т. к. он в другой ветке...

11. **создадим file2.txt, закоммитим изменение:**
```git
[main 67a77fa] создал file2.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 file2.txt
```

12. **git log:**
```git 
* 67a77fa (HEAD -> main) создал file2.txt
| * 15d2900 (mybranch) создал файл file1.txt
|/  
* 55db97b (origin/main) теперь точно добавил коммент в первую строку
* c6b06e2 добавил коммент в первую строку
* 9e4d180 Добавили
* b7dd34a (bulochka/main) Delete programming_C directory
* 2dfcd52 Delete Hello_world.c
* d38fba1 Update Hello_world.c
* 521423f hello_world.c
* e20c128 Hello_world.c
```
видим, что верхушка дерева разделилась на две ветки: main и mybranch

13-14. **при переходе на ветку mybranch file2.txt пропал...**

15. **git diff:**
```
diff --git a/file1.txt b/file2.txt
similarity index 100%
rename from file1.txt
rename to file2.txt
```
тут нам говорят о том, что file1.txt был переименован в file2.txt, а содержимое совпадает на 100%, потому что они пустые

16. **создал Очень важный документ.docx, закоммитил и запушил на удаленку:**
```git 
Enumerating objects: 9, done.
Counting objects: 100% (9/9), done.
Delta compression using up to 12 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (8/8), 69.87 KiB | 11.64 MiB/s, done.
Total 8 (delta 0), reused 0 (delta 0), pack-reused 0
remote: 
remote: Create a pull request for 'mybranch' on GitHub by visiting:
remote:      https://github.com/Hadomir01/bulochka/pull/new/mybranch
remote: 
To https://github.com/Hadomir01/bulochka
 * [new branch]      mybranch -> mybranch
branch 'mybranch' set up to track 'origin/mybranch'.
```
на удаленке была создана новая ветка:
![alt text](image-1.png)

17. **вернемся к старой ветке и запушим её:**
```git
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 12 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 294 bytes | 294.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/Hadomir01/bulochka
   55db97b..67a77fa  main -> main
branch 'main' set up to track 'origin/main'.
```
обновил удаленную ветку main:s
![alt text](image-2.png)
</details>