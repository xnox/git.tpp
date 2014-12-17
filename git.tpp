--bgcolor white
--fgcolor black
--title git --fast-version-control
--author by Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
--date today

-dsdfsfsfs--
--newpage
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

--newpage
* Set the name
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
--endslidetop

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

--newpage

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

--newpage
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
--endshelloutput
--newpage
* Check your work
--beginshelloutput
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

--newpage
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

--newpage
--beginshelloutput
$ git pull olav master

  *** BOOM ***
--endshelloutput
--beginshelloutput
Merge branch 'master' of ../olav

# Please enter a commit message to explain why this merge is necessary,
# especially if it merges an updated upstream into a topic branch.
#
# Lines starting with '#' will be ignored, and an empty message aborts
# the commit.
--endshelloutput
--beginshelloutput
$ git pull olav master
From ../olav
 * branch            master     -> FETCH_HEAD
Auto-merging hello.py
Waiting for Emacs...
Merge made by the 'recursive' strategy.
 hello.py | 2 ++
 1 file changed, 2 insertions(+)

--endshelloutput

--newpage
--beginshelloutput
$ git log --decorate --all --graph
*   commit 57779961e93dd31eae1c50274c1f4bd55d77e17f (HEAD, master)
|\  Merge: 9c25a24 36c02f6
| | Author: Duke of Weselton <duke.weselton@example.com>
| | Date:   Wed Dec 17 21:57:58 2014 +0000
| | 
| |     Merge branch 'master' of ../olav
| |   
| * commit 36c02f65c6129cc77f52cc3069cb08069db414b1 (olav/master)
| | Author: Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
| | Date:   Wed Dec 17 21:30:19 2014 +0000
| | 
| |     Add comment
| |   
* | commit 9c25a249c3b898e7aaf7734e3a2c44e90ecf50b7 (feature-a)
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
--beginshelloutput
$ git push olav master:master
Counting objects: 3, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 400 bytes | 0 bytes/s, done.
Total 3 (delta 0), reused 0 (delta 0)
To ../olav
   36c02f6..5777996  master -> master
--endshelloutput

--newpage
--beginshelloutput
$ cat .git/HEAD
ref: refs/heads/master

$ cat .git/refs/heads/master
57779961e93dd31eae1c50274c1f4bd55d77e17f

$ git cat-file -p 57779961e93dd31eae1c50274c1f4bd55d77e17f
tree 818e82acb72eaeea52dea6f1966e9f2a33c011c4
parent 9c25a249c3b898e7aaf7734e3a2c44e90ecf50b7
parent 36c02f65c6129cc77f52cc3069cb08069db414b1
author Duke of Weselton <duke.weselton@example.com> 1418853478 +0000
committer Duke of Weselton <duke.weselton@example.com> 1418853478 +0000

Merge branch 'master' of ../olav
--endshelloutput

--beginshelloutput
$ git show HEAD:hello.py
# Hello World implementation

def hello():
    print("Hello World!")

def bye():
    print("Good Bye!")
--endshelloutput

--newpage
--beginshelloutput
$ echo "No docs yet" > README
$ git add README
$ git commit -m "Add RAEMDE"
[master 023a7e7] Add RAEMDE
 1 file changed, 1 insertion(+)
 create mode 100644 README
--endshelloutput

--beginshelloutput
$ git mv README README.txt
$ git commit --amend

*** BOOM ***
--endshelloutput
--beginoutput
Add RAEMDE

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# Date:      Wed Dec 17 22:06:00 2014 +0000
#
# On branch master
# Changes to be committed:
#       new file:   README.txt
#

--endoutput
--newpage
--beginshelloutput
$ git commit --amend
Waiting for Emacs...
[master b74c79a] Add README
 Date: Wed Dec 17 22:06:00 2014 +0000
 1 file changed, 1 insertion(+)
 create mode 100644 README.txt
--endshelloutput

--newpage
--beginshelloutput
$ git reflog
b74c79a HEAD@{0}: commit (amend): Add README
023a7e7 HEAD@{1}: commit: Add RAEMDE
5777996 HEAD@{2}: pull olav master: Merge made by the 'recursive' strategy.
9c25a24 HEAD@{3}: merge feature-a: Fast-forward
e01f5fa HEAD@{4}: checkout: moving from feature-a to master
9c25a24 HEAD@{5}: commit: Bye
e01f5fa HEAD@{6}: checkout: moving from master to feature-a
e01f5fa HEAD@{7}: commit (initial): Initial commit
--endshelloutput
* Go back in time
--beginshelloutput
$ git reset --hard 9c25a24
HEAD is now at 9c25a24 Bye

$ git log --oneline
9c25a24 Bye
e01f5fa Initial commit

$ git rebase olav/master 
First, rewinding head to replay your work on top of it...
Applying: Bye
Using index info to reconstruct a base tree...
M     hello.py
Falling back to patching base and 3-way merge...
Auto-merging hello.py
--endshelloutput

--newpage
* Rebase generates linear history
--beginoutput
$ git log --oneline --graph
* b6554fa Bye
* 36c02f6 Add comment
* e01f5fa Initial commit
--endoutput

(Recall previous result of a merge)
--beginoutput
$ git log --oneline --graph 5777996
*   5777996 Merge branch 'master' of ../olav
|\  
| * 36c02f6 Add comment
* | 9c25a24 Bye
|/  
* e01f5fa Initial commit
--endoutput
* Merge preserves history as it happened

--newpage
* Black voodoo, reorder, delete, add things in the history
--beginshelloutput
$ git rebase -i --root
*** BOOM ***
--endshelloutput
--beginoutput
pick e01f5fa Initial commit
pick 36c02f6 Add comment
pick b6554fa Bye

# Rebase b6554fa onto c89757e
#
# Commands:
#  p, pick = use commit
#  r, reword = use commit, but edit the commit message
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#  f, fixup = like "squash", but discard this commit's log message
#  x, exec = run command (the rest of the line) using shell
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out
--endoutput
--newpage
--beginoutput
e 5dffa27 Initial commit
r d6509fd Bye
p 7a73e21 Add comment


# Rebase d6509fd onto 832cef2
#
# Commands:
#  p, pick = use commit
#  r, reword = use commit, but edit the commit message
#  e, edit = use commit, but stop for amending
#  s, squash = use commit, but meld into previous commit
#  f, fixup = like "squash", but discard this commit's log message
#  x, exec = run command (the rest of the line) using shell
#
# These lines can be re-ordered; they are executed from top to bottom.
#
# If you remove a line here THAT COMMIT WILL BE LOST.
#
# However, if you remove everything, the rebase will be aborted.
#
# Note that empty commits are commented out
--endoutput
--newpage
--beginshelloutput
$ git rebase -i --root
Waiting for Emacs...
Stopped at 5dffa2741b12af6f9b16a160804c84e5c0973a9b... Initial commit
You can amend the commit now, with

    git commit --amend 

Once you are satisfied with your changes, run

     git rebase --continue

$ touch LICENSE
$ git add LICENSE
$ git commit -m "Add LICENSE"
[detached HEAD a2fd685] Add LICENSE
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 LICENSE

$ git rebase --continue
--endshelloutput
--newpage
--beginoutput
Bye

# Please enter the commit message for your changes. Lines starting
# with '#' will be ignored, and an empty message aborts the commit.
#
# Author:    Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
# Date:      Wed Dec 17 21:23:00 2014 +0000
#
# rebase in progress; onto 832cef2
# You are currently editing a commit while rebasing branch 'master' on '832cef2'.
#
# Changes to be committed:
#       modified:   hello.py
#
--endoutput
--beginshelloutput
$ git rebase --continue
Waiting for Emacs...
[detached HEAD 17c9eea] Implement Good Bye function
 Author: Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
 Date: Wed Dec 17 21:23:00 2014 +0000
 1 file changed, 3 insertions(+)
Successfully rebased and updated refs/heads/master.
--endshelloutput
--newpage
--beginshelloutput
$ git log --decorate --graph
* commit 75d87b06852253ec453cc6a038978991fcc9c801 (HEAD, master)
| Author: Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
| Date:   Wed Dec 17 21:30:19 2014 +0000
| 
|     Add comment
|  
* commit 17c9eeaf4af4eb533dce0fcdafcc9dc75b33c32c
| Author: Dimitri John Ledkov <dimitri.j.ledkov@intel.com>
| Date:   Wed Dec 17 21:23:00 2014 +0000
| 
|     Implement Good Bye function
|  
* commit a2fd6853460b5ad33e3bf0c058867e5a46831440
| Author: Duke of Weselton <duke.weselton@example.com>
| Date:   Wed Dec 17 22:33:29 2014 +0000
| 
|     Add LICENSE
|  
* commit 4c77e255a592880477ca42405ed78ea5b64b7631
  Author: Duke of Weselton <duke.weselton@example.com>
  Date:   Wed Dec 17 20:58:49 2014 +0000
  
      Initial commit
--endshelloutput