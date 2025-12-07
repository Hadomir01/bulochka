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
...
```

![alt text](imgs/image.png)
Всего у меня получилось 8 коммитов. Почему? Просто чуть ранее я решил немного поиграться с гитом: посоздавал файлы, папки, поудалаял их.

## Теперь задания с ветками

1-2. **создаем новую ветку...**

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
...
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
...
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
![alt text](imgs/image-1.png)

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
обновил удаленную ветку main:
![alt text](imgs/image-2.png)
</details>

<details>
<summary> На 4... </summary>

## На оценку 4

1. **вернемся на ветку mybranch**

2. **добавим в sort.c функцию main:**
```c
int main() {
    int a[3] = {1, 2, 3};
    bubbleSort(a, 3);
}
```

3-4. **git diff:**
```git
diff --git a/sort.c b/sort.c
index eca8ac4..e79feec 100644
--- a/sort.c
+++ b/sort.c

...

+
+int main() {
+    int a[3] = {1, 2, 3};
+    bubbleSort(a, 3);
+}
\ No newline at end of file
```
сейчас показывает последнее добавленное изменение, а **git diff --staged** пустой... 

5-7. **добавим в staged и посмотрим, что теперь говорят git diff и git diff --staged**

git diff пустой... а git diff --staged:
```
diff --git a/sort.c b/sort.c
index eca8ac4..e79feec 100644
--- a/sort.c
+++ b/sort.c

...

+
+int main() {
+    int a[3] = {1, 2, 3};
+    bubbleSort(a, 3);
+}
\ No newline at end of file
```
т. е. показывает тоже, что и git diff до добавления файла в staged...

8-10. **продолжаем эксперимент. снова изменим файл и посмотри вывод команд...**

git diff:
```git
diff --git a/sort.c b/sort.c
index e79feec..75126f9 100644
--- a/sort.c
+++ b/sort.c

...

 int main() {
-    int a[3] = {1, 2, 3};
+    int a[3] = {1, 2};
     bubbleSort(a, 3);
 }
\ No newline at end of file
```

git diff --staged:
```git
diff --git a/sort.c b/sort.c
index eca8ac4..e79feec 100644
--- a/sort.c
+++ b/sort.c

...

+
+int main() {
+    int a[3] = {1, 2, 3};
+    bubbleSort(a, 3);
+}
\ No newline at end of file
```

11. **что же здесь происходит?**

Дело в том, что git diff показывает изменения файлов, еще не добавлленных в staged, а git diff --staged показывает изменения файлов уже в staged. Так как мы не коммитили предпоследнее изменение sort.c, он все еще находится в staged и --staged учитывает и это изменение. поэтому если мы пропишем git status, то увидим sort.c дважды...

12. **git status:**
```git
On branch mybranch
Your branch is up to date with 'origin/mybranch'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   sort.c

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   sort.c
...
```
да, sort.c встретился дважды...

13. **вернем отправленный в staged sort.c назад**

14. **git status:**
```git
On branch mybranch
Your branch is up to date with 'origin/mybranch'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   sort.c
...
```
теперь показывается только 1 sort.c (тот, где мы удаляли один элемент из массива)

15. **теперь индексируем и коммитим...**

16. **git log:**
```git
commit 007a4da4df17530e584755eb4d5a476cfe35f503 (HEAD -> mybranch)
Author: Hadomir01 <okser0656@gmail.com>
Date:   Sat Dec 6 19:53:39 2025 +0700

    Изменил sort.c

commit 786a58983793f0b615dce6ac6169090cfaac6163 (origin/mybranch)
Author: Hadomir01 <okser0656@gmail.com>
Date:   Sat Dec 6 18:07:41 2025 +0700

    создал файл с фотографиями
...
```
git log с графиком:
```git
* 007a4da (HEAD -> mybranch) Изменил sort.c
* 786a589 (origin/mybranch) создал файл с фотографиями
* 15d2900 создал файл file1.txt
| * 6a441f6 (origin/main, main) Доп. изменения README.md
| * f375a8e Отредактировал README.md
| * 5f6b963 добавил README.md и фоточки к нему
| * 67a77fa создал file2.txt
|/  
* 55db97b теперь точно добавил коммент в первую строку
...
```
указатель HEAD на ветку mybranch

17-18. **отредактируем sort.c снова, добавив printf()**
```c
...
int main() {
    int a[3] = {1, 2};
    bubbleSort(a, 2);
    printf("hello git!\n");
}
```

19. **git status:**
```git
On branch mybranch
Your branch is ahead of 'origin/mybranch' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   sort.c
...
```
говорит, что у нас есть измененный sort.c и ветка mybranch содержит 1 новый коммит...

20-22. **git restore sort.c восстановил наш файл до закоммиченного состояния:**
```c
...
int main() {
    int a[3] = {1, 2};
    bubbleSort(a, 3);
}
```
а git status скажет:
```git
On branch mybranch
Your branch is ahead of 'origin/mybranch' by 1 commit.
  (use "git push" to publish your local commits)
...
```
что у нас нет измененных файлов, есть только 1 коммит

23. **запушим этот коммит на удаленку**

вот как выглядит mybranch на удаленке
![alt text](imgs/image-3.png)

и если мы проверим sort.c ...

![alt text](imgs/image-4.png)

сохранились изменения без printf

## теперь поиграемся с ff-merge

1. **создадим файл greeting.txt и закоммитим это изменение**

```git 
[mybranch 8addf7b] Add file greeting.txt
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 greeting.txt
```

2. **добавим в новый файл "hello!". Закоммитим изменение**

```git 
[mybranch f27d53d] Add content to greeting.txt
 1 file changed, 1 insertion(+)
```

3-4. **создадим новую ветку и перейдем в нее**

```git
Switched to branch 'feature/uppercase'
```

5. **git status:**
```git
On branch feature/uppercase
nothing to commit, working tree clean
```
тут пусто...

6-7. **изменим содержимое файла и закоммитим...**

8. **git branch:**
```git
* feature/uppercase
  main
  mybranch
```
показывает, что мы в feature/uppercase...

9. **git log:**
```git
* 0a4646d (HEAD -> feature/uppercase) Изменил регистр надписи в greetings.txt
* f27d53d (mybranch) Add content to greeting.txt
* 8addf7b Add file greeting.txt
* 531fadb (origin/mybranch) Добавил .gitignore
* 007a4da Изменил sort.c
* 786a589 создал файл с фотографиями
* 15d2900 создал файл file1.txt
| * 7b871d9 (origin/main, main) Новые добавления README.md (оценка 4)
| * 6a441f6 Доп. изменения README.md
...
```

10-11. **перейдем в основную ветку и посмотрим на содержимое greeting.txt**

```bash
cat: greeting.txt: No such file or directory
```
в основной ветке такого файла нет, он есть только в mybranch и feature/uppercase

значит, идем в ветку mybranch...
здесь команда cat выводит "hello!"

12. **сравним ветки mybranch и feature/uppercase**

```git
diff --git a/greeting.txt b/greeting.txt
index 3462721..29adda4 100644
--- a/greeting.txt
+++ b/greeting.txt
@@ -1 +1 @@
-hello!
\ No newline at end of file
+HELLO!
\ No newline at end of file
```
разница в надписях: в одной веткона в нижнем регистре, в другой в верхнем...

13. **объединим ветки mybranch и feature/uppercase**
```git
Updating f27d53d..0a4646d
Fast-forward
 greeting.txt | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```

14. **проверим содержимое командой cat:**
```bash
HELLO!
```
вывел надпись в верхнем регистре(последнее изменение)

15. **удалим feature/uppercase:**
```git
Deleted branch feature/uppercase (was 0a4646d).
```

16. **смержим ветки mybranch и main, перейдя в main**
```git
Merge made by the 'ort' strategy.
...                                                 
6 files changed, 7 insertions(+)
```

17. **git log:**
```git
*   8177c49 (HEAD -> main) Смержил mybranch в main
|\  
| * 0a4646d (mybranch) Изменил регистр надписи в greetings.txt
| * f27d53d Add content to greeting.txt
| * 8addf7b Add file greeting.txt
| * 531fadb (origin/mybranch) Добавил .gitignore
| * 007a4da Изменил sort.c
```
самый последний коммит - merge commit хранит объединение веток main и mybranch

</details>

<details>
<summary> На 5... </summary>

## На оценку 5

1-3. **создадим новую ветку branch1 и файл в ней с надписью. закоммитим это изменение**


4-5. **вернемся в main и проделаем то же самое, только с друогой надписью. также закоммитим изменение**

6. **git log:**
```git
* 0b0a586 (HEAD -> main) Добавил file.txt
| * 67ac845 (branch1) Добавил file.txt
|/  
* ea83e61 (origin/main) обновил README.md до 4+
*   8177c49 Смержил mybranch в main
```
два разных коммита содержат изменения одинаковых строк.

7. **попробуем смержить branch1 в main**
```git 
Auto-merging file.txt
CONFLICT (add/add): Merge conflict in file.txt
Automatic merge failed; fix conflicts and then commit the result.
```
возник merge-конфликт, так как git не знает, какое изменение брать за основу...

8. **git status:**
```git 
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

You have unmerged paths.
  (fix conflicts and run "git commit")
  (use "git merge --abort" to abort the merge)

Unmerged paths:
  (use "git add <file>..." to mark resolution)
        both added:      file.txt
```

9. **попробуем избавиться от конфликта, приняв текущее изменение(ветки main)**

10. **git log:**
```git
* 0b0a586 (HEAD -> main) Добавил file.txt
* ea83e61 (origin/main) обновил README.md до 4+
*   8177c49 Смержил mybranch в main
```
нет коммита из ветки branch1


## теперь попробуем починить m-конфликт для программы на python

1-2. **создадим mergesort.py и добавим туда код... закоммитим изменение**

3. **теперь создадим новую ветку Mergesort-Impl...**

4-5. **в этой ветке заменим содержимое mergesort.py... не забудем закоммитить изменения**

```git
[Mergesort-Impl 62e129a] Изменил mergesort.py
 1 file changed, 36 insertions(+), 3 deletions(-)
```

6-7. **возвращаемя в main и меняем содержимое mergesort.py... коммитим изменение**

```git
[main 5aed88e] Изменил mergesort.py
 1 file changed, 35 insertions(+), 3 deletions(-)
```

8. **git log:**

```git
* 5aed88e (HEAD -> main) Изменил mergesort.py
* 0b39ada Создал mergesort.py
*   77de7d9 (origin/main) Merge branch 'branch1'
...
```
показывает коммит изменения mergesort.py в main

а если прописать git log --oneline --graph -all (git lol):
```git
* 5aed88e (HEAD -> main) Изменил mergesort.py
| * 62e129a (Mergesort-Impl) Изменил mergesort.py
|/  
* 0b39ada Создал mergesort.py
...
```
из одного коммита, где был создан mergesort.py исходят 2 коммита, где файл был изменен

9. **git branch:**
```git
  Mergesort-Impl
  branch1
* main
  mybranch
```

10. **попробуем смержить Mergesort-Impl в main**

```git 
Auto-merging mergesort.py
CONFLICT (content): Merge conflict in mergesort.py
Automatic merge failed; fix conflicts and then commit the result.
```
возник m-конфликт, который нужно исправить
</details>