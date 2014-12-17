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

---
--newpage
  * Inspect data structures
--beginshelloutput
$ cat .git/HEAD 
ref: refs/heads/master

$ cat .git/refs/heads/master 
e01f5fadae32d548764e977800d3ad53382b024f

$ file .git/objects/e0/1f5fadae32d548764e977800d3ad53382b024f 
.git/objects/e0/1f5fadae32d548764e977800d3ad53382b024f: VAX COFF executable - version 30940

$ git cat-file -p e01f5fadae32d548764e977800d3ad53382b024f
tree 5a5835b0d3aecf490a9050eb4a4974f2e0b9c2f9
author Duke of Weselton <duke.weselton@example.com> 1418849929 +0000
committer Duke of Weselton <duke.weselton@example.com> 1418849929 +0000

Initial commit

$ git cat-file -p 5a5835b0d3aecf490a9050eb4a4974f2e0b9c2f9
100644 blob 34fcef1ac18f5955009350ceec8daff985301e00	.gitignore
100644 blob 4ddabcbf559ea9ddaa8c7b52fd57423176191384	hello.py


$ git cat-file -p 34fcef1ac18f5955009350ceec8daff985301e00
*.pyo
*.pyc
--endshelloutput

---
--newpage
  * Let's make a feature and merge it back in
--beginshelloutput
$ git checkout -b feature-a
Switched to a new branch 'feature-a'

$ cat >> hello.py << EOF

def bye():
    print("Good Bye!")
EOF

$ git add hello.py

$ git commit -m "Bye"
[feature-a 9c25a24] Bye
 1 file changed, 3 insertions(+)

$ git checkout master
Switched to branch 'master'

$ git merge feature-a
Updating e01f5fa..9c25a24
Fast-forward
 hello.py | 3 +++
 1 file changed, 3 insertions(+)
--endshelloutput

---
--newpage
  * Let's share with olav
--beginshelloutput
$ git remote add olav ../olav

$ git remote update
Fetching olav
remote: Counting objects: 3, done.
remote: Compressing objects: 100% (3/3), done.
remote: Total 3 (delta 0), reused 0 (delta 0)
Unpacking objects: 100% (3/3), done.
From ../olav
 * [new branch]      master     -> olav/master
--endshelloutput

--beginshelloutput
$ git push olav master:master
To ../olav
 ! [rejected]        master -> master (non-fast-forward)
error: failed to push some refs to '../olav'
hint: Updates were rejected because the tip of your current branch is behind
hint: its remote counterpart. Integrate the remote changes (e.g.
hint: 'git pull ...') before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.
--endshelloutput

--beginshelloutput
$ git log --decorate --all --graph
* commit 36c02f65c6129cc77f52cc3069cb08069db414b1 (olav/master)
| Author: Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
| Date:   Wed Dec 17 21:30:19 2014 +0000
| 
|     Add comment
|    
| * commit 9c25a249c3b898e7aaf7734e3a2c44e90ecf50b7 (HEAD, master, feature-a)
|/  Author: Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
|   Date:   Wed Dec 17 21:23:00 2014 +0000
|   
|       Bye
|  
* commit e01f5fadae32d548764e977800d3ad53382b024f
  Author: Duke of Weselton <duke.weselton@example.com>
  Date:   Wed Dec 17 20:58:49 2014 +0000
  
      Initial commit
--endshelloutput