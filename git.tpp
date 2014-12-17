--bgcolor white
--fgcolor black
--title git --fast-version-control
--author by Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
--date today

---
  * Start a new project

--beginshelloutput
$ git init olav
Initialised empty Git repository in /home/djledkov/temp/olav/.git/
--endshelloutput

--beginshelloutput
$ mkdir elsa
$ cd elsa
$ git init .
Initialised empty Git repository in /home/djledkov/temp/elsa/.git/
--endshelloutput

---
--newpage
  * Hi, my name is...
--beginshelloutput
$ git config --global user.name "Duke of Weselton"
$ git config --global user.email "duke.weselton@example.com"
--endshelloutput

--beginshelloutput
$ cat ~/.gitconfig
[user]
	name = Duke of Weselton
	email = duke.weselton@example.com
--endshelloutput

---
  * Let's make a commit
--beginshelloutput
$ cat > hello.py << EOF
def hello():
    print("Hello World!")
EOF
$ python -c "import hello"
$ python -O -c "import hello"
$ ls 
hello.py  hello.pyc  hello.pyo
--endshelloutput

---
--newpage
  * We want to commit source code only
--beginshelloutput
$ git status
On branch master

Initial commit

Untracked files:
  (use "git add <file>..." to include in what will be committed)

--color red
  hello.py
  hello.pyc
  hello.pyo
--color black

nothing added to commit but untracked files present (use "git add" to track)
--endshelloutput

--beginshelloutput
$ git add hello.py
$ git status
On branch master

Initial commit

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

--color green
  new file:   hello.py
--color black

Untracked files:
  (use "git add <file>..." to include in what will be committed)

--color red
  hello.pyc
  hello.pyo
--color black

--endshelloutput

---
--newpage
  * Let's ignore build by-products
--beginshelloutput
$ cat > .gitignore << EOF
*.pyo
*.pyc
EOF
$ git status
On branch master

Initial commit

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

--color green
  new file:   hello.py
--color black

Untracked files:
  (use "git add <file>..." to include in what will be committed)

--color red
  .gitignore
--color black

--endshelloutput

--beginshelloutput
$ git add .gitignore
$ git status
On branch master

Initial commit

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

--color green
  new file:   hello.py
  new file:   .gitignore
--color black

--endshelloutput

---
--newpage
  * Our first commit
--beginshelloutput
$ git commit -m "Initial commit"
[master (root-commit) 1f3e3e3] Initial commit
 2 files changed, 4 insertions(+)
 create mode 100644 .gitignore
 create mode 100644 hello.py

$ git status
On branch master
nothing to commit, working directory clean

$ git log -p
--color yellow
commit e01f5fadae32d548764e977800d3ad53382b024f
--color black
Author: Duke of Weselton <duke.weselton@example.com>
Date:   Wed Dec 17 20:58:49 2014 +0000

    Initial commit

diff --git a/.gitignore b/.gitignore
new file mode 100644
index 0000000..34fcef1
\--- /dev/null
+++ b/.gitignore
--color cyan
@@ -0,0 +1,2 @@
--color green
+*.pyo
+*.pyc
--color black
diff --git a/hello.py b/hello.py
new file mode 100644
index 0000000..4ddabcb
\--- /dev/null
+++ b/hello.py
--color cyan
@@ -0,0 +1,2 @@
--color green
+def hello():
+    print("Hello World!")
--color black
--endshelloutput

  * But we had build by-products ...
  * ... clean them!
--beginshelloutput
$ git clean -f -x -d
Removing hello.pyc
Removing hello.pyo
--endshelloutput
