# Git
- [Setup \& Config](#setup--config)

## Links <!-- omit from toc -->
- [Git Commands Cheatsheet](https://www.reddit.com/r/git/comments/1oj159s/git_commands_cheat_sheet_what_should_i_add_or_fix/)
- [Git Documentation](https://git-scm.com/docs)

## Init
- 
  |                                                 |                                     |
  | ----------------------------------------------- | ----------------------------------- |
  | `git init`                                      | start new local repo                |
  | `git clone <url>`                               | clone repo from remote              |
  | `git clone --branch <branch> <url>`             | clone remote repo + checkout branch |
  | `git config --global core.editor "code --wait"` | use VS-Code as git editor           |

## Basic Workflow
- 
  |                      |                                                             |
  | -------------------- | ----------------------------------------------------------- |
  | `git status`         | check status of files (un-tracked, un-staged, un-committed) |
  | `git add <file>`     | stage file                                                  |
  | `git add -p`         | interactively review & stage every change hunk              |
  | `git commit`         | commit, but supports multi-line commit message              |
  | `git commit -v`      | commit + diff                                               |
  | `git commit --amend` | edit last commit                                            |
  | `git log`            | show commit history                                         |
  | `git log --oneline`  | pretty log view                                             |
  | `git diff`           | show un-staged changes                                      |
  | `git diff --staged`  | show staged diff                                            |
- `git add .`/`git add -A` discouraged to prevent accidently staging untracked files  
  `git commit -m <msg>` discouraged to write multi-line commit messages

## Branching
- 
  |                                   |                                    |
  | --------------------------------- | ---------------------------------- |
  | `git branch`                      | list branches                      |
  | `git branch <name>`               | create new branch                  |
  | `git switch <name>`               | switch to branch                   |
  | `git switch -c <name>`            | create branch + switch branch      |
  | `git merge <branch>`              | merge branch into current          |
  | `git rebase <branch>`             | rebase current onto another branch |
  | `git branch -d <name>`            | delete local branch                |
  | `git push --delete origin <name>` | delete remote branch               |
  | `git checkout <commit>`           | go-to specific commit              |
  | `git cherry-pick <commit>`        | apply specific commit              |
- `checkout` can also checkout both files & branches, instead use `switch` & `restore`

## Remote
- 
  |                               |                                            |
  | ----------------------------- | ------------------------------------------ |
  | `git remote -v`               | show remotes                               |
  | `git remote add origin <url>` | add remote origin (usually empty repo)     |
  | `git push -u origin main`     | push first time                            |
  | `git push`                    | push changes                               |
  | `git pull`                    | pull latest changes + merge local commits  |
  | `git pull --rebase`           | pull remote changes + rebase local commits |
  | `git fetch`                   | fetch branches/tags from default remote    |
  | `git fetch --prune`           | remove deleted remotes                     |
- `git pull` refuses to work with un-committed files, so stash them first

## Undo & Fix
- 
  |                                    |                                                          |
  | ---------------------------------- | -------------------------------------------------------- |
  | `git restore <file>`               | discard local changes in file                            |
  | `git reset <file>`                 | unstage a file, changes kept                             |
  | `git reset --hard`                 | reset to last commit                                     |
  | `git reset --hard <commit>`        | reset to commit                                          |
  | `git reset --hard origin/<branch>` | reset to remote branch                                   |
  | `git revert <commit>`              | new commit undoing old one                               |
  | `git reflog`                       | local-only recycle bin (lost commits) & history          |
  | `git clean -fd`                    | permanently delete untracked files & folders (no reflog) |
  | `git clean -nd`                    | dry run that lists untracked files                       |
  | `git clean -fdx`                   | delete untracked & ignored files                         |

## Stash
- 
  |                               |                           |
  | ----------------------------- | ------------------------- |
  | `git stash`                   | save un-committed changes |
  | `git stash pop`               | apply last stash          |
  | `git stash list`              | show stash list           |
  | `git stash apply 'stash@{n}'` | apply specific stash      |
  | `git stash drop 'stash@{n}'`  | remove specific stash     |

## Tags
- 
  |                          |                 |
  | ------------------------ | --------------- |
  | `git tag <tag>`          | create tag      |
  | `git tag`                | list tags       |
  | `git tag -d <tag>`       | delete tag      |
  | `git push origin <tag>`  | sush single tag |
  | `git push origin --tags` | sush all tags   |

## History
- 
  |                                |                                      |
  | ------------------------------ | ------------------------------------ |
  | `git show <commit>`            | show changes in specific commit      |
  | `git blame <file>`             | show which commit modified each line |
  | `git blame -L 50,60 <file>`    | commit for [50, 60] lines            |
  | `git blame -L 50,+10 <file>`   | commit for [50, 50+10] lines         |
  | `git blame -L :foo <file>`     | commit for lines in foo function     |
  | `git shortlog -sn`             | show num commits per author          |
  | `git log --since="2026-03-01"` | filter commits by date               |
  | `git log -p <file>`            | show file history with commit + diff |

## Interactive Rebase
- `git rebase -i HEAD~n` to modify last n commits
- shows commits in oldest-to-newest order in the editor
  ```sh
  pick a1b2c3d Add feature
  pick e5f6g7h Fix typo
  pick i9j0k1l Actually fix typo
  ```
- can apply one of below actions
  - `pick`: **(default)** keep commit as is
  - `reword`: keep commit but change log message
  - `edit`: amend files in that commit
  - `squash`: meld commit with one listed above it, and combine messages
  - `fixup`: like squash, but discards message
  - `drop`: deletes commit entirely
- git starts executing actions once editor saved & exited
- ***Example:* Squashing:** below actions will create one clean commit `"Add feature"`
  ```sh
  pick a1b2c3d Add feature
  fixup e5f6g7h Fix typo
  fixup i9j0k1l Actually fix typo
  ```