# Git
- [Init](#init)
- [Basic Workflow](#basic-workflow)
- [Branching](#branching)
- [History Cleanup](#history-cleanup)
- [Remote](#remote)
- [Undo \& Fix](#undo--fix)
- [Stash](#stash)
- [Tags](#tags)
- [History](#history)

## Links <!-- omit from toc -->
- [Git Guide](https://rogerdudler.github.io/git-guide/)
- [Git Commands Cheatsheet](https://www.reddit.com/r/git/comments/1oj159s/git_commands_cheat_sheet_what_should_i_add_or_fix/)
- [Git Documentation](https://git-scm.com/docs)

## Init
- **Four Areas of Git:**
  ```mermaid
  graph TD
      WD[Working Directory]
      SA[Staging Area]
      LR[Local Repo]
      RR[Remote Repo]

      WD -- add --> SA
      SA -- commit --> LR
      LR -- push --> RR
      RR -- fetch --> LR
      RR -- pull --> WD
      LR -- switch --> WD
      SA -- restore --> WD
  ```
- ㅤ
  |                                                 |                            |
  | ----------------------------------------------- | -------------------------- |
  | `git init`                                      | create local repo          |
  | `git clone <url>`                               | clone existing remote repo |
  | `git clone --branch <branch> <url>`             | clone then switch branch   |
  | `git config --global core.editor "code --wait"` | set `code` as git editor   |

## Basic Workflow
- ㅤ
  |                      |                                |
  | -------------------- | ------------------------------ |
  | `git status`         | file status                    |
  | `git add <file>`     | stage file                     |
  | `git add -p`         | stage by reviewing each change |
  | `git commit`         | commit staged changes          |
  | `git commit --amend` | edit last commit               |
  | `git log`            | show commit history            |
  | `git log --oneline`  | pretty log view                |
  | `git diff`           | show un-staged changes         |
  | `git diff --staged`  | show staged diff               |
- **NOTE:** `add -A` and ` commit -m` are discouraged to prevent staging untracked files and to promote multi-line commit messages

## Branching
- ㅤ
  |                                   |                                    |
  | --------------------------------- | ---------------------------------- |
  | `git branch`                      | list branches                      |
  | `git branch <name>`               | create branch                      |
  | `git switch <name>`               | switch to branch                   |
  | `git switch -c <name>`            | create branch then switch to it    |
  | `git merge <branch>`              | merge branch into current          |
  | `git rebase <branch>`             | rebase current onto another branch |
  | `git branch -d <name>`            | delete local branch                |
  | `git push --delete origin <name>` | delete remote branch               |
  | `git switch --detach <commit>`    | go-to specific commit              |
  | `git cherry-pick <commit>`        | apply specific commit's changes    |
- **NOTE:** `checkout` can used for files, commits, tags & branches, instead use modern alternatives `switch` & `restore`

## History Cleanup
- **Interactive Rebase:** `git rebase -i HEAD~n` will modify last `n` commits
- **Actions:** git starts executing actions once editor is saved and exited
  - `pick`: (default) keep commit as is
  - `reword`: keep commit but change message
  - `edit`: pause rebase to amend files in that commit
  - `squash`: meld into previous commit and combine messages
  - `fixup`: meld into previous, but discards its message
  - `drop`: deletes commit entirely
- ***Example:* Squashing Fixes:** create one clean `"Add feature"` commit
  ```sh
  pick    a1b2c3d   Add feature
  fixup   e5f6g7h   Fix typo
  fixup   i9j0k1l   Actually fix typo
  ```

## Remote
- ㅤ
  |                     |                                                           |
  | ------------------- | --------------------------------------------------------- |
  | `git push`          | push changes to remote                                    |
  | `git fetch`         | fetch changes from remote                                 |
  | `git fetch --prune` | local cleanup of deleted remote branches                  |
  | `git pull`          | fetch remote commits then merge into current branch       |
  | `git pull --rebase` | fetch remote commits then rebase current branch onto them |
- **NOTE:** `git pull` can fail on conflicts with local uncommitted files, so stash them first

## Undo & Fix
- ㅤ
  |                                    |                                               |
  | ---------------------------------- | --------------------------------------------- |
  | `git restore <file>`               | discard local unstaged changes in file        |
  | `git restore --staged <file>`      | unstage file but keep actual changes          |
  | `git reset --hard <branch/commit>` | wipe local changes                            |
  | `git revert <commit>`              | create new commit that reverses old commit    |
  | `git reflog`                       | local history log (including deleted commits) |

## Stash
- ㅤ
  |                               |                                              |
  | ----------------------------- | -------------------------------------------- |
  | `git stash`                   | save un-committed changes to temporary stack |
  | `git stash list`              | list all stashed changes                     |
  | `git stash pop`               | apply (then delete) most recent stash        |
  | `git stash apply 'stash@{n}'` | apply specific stash (but keep it in stack)  |
  | `git stash drop 'stash@{n}'`  | delete specific stash from stack             |

## Tags
- ㅤ
  |                             |                           |
  | --------------------------- | ------------------------- |
  | `git tag <tag>`             | create tag                |
  | `git tag`                   | list all tags             |
  | `git tag -d <tag>`          | delete local tag          |
  | `git push origin <tag>`     | push single tag to remote |
  | `git push origin --tags`    | push all tags to remote   |
  | `git switch --detach <tag>` | go-to specific tag        |

## History
- ㅤ
  |                                |                                         |
  | ------------------------------ | --------------------------------------- |
  | `git show <commit>`            | show changes in specific commit         |
  | `git blame <file>`             | show which commit modified each line    |
  | `git blame -L A,B <file>`      | blame for specific line range           |
  | `git blame -L A,+B <file>`     | blame for `B` lines from line `A`       |
  | `git blame -L :foo <file>`     | blame for code inside function `foo`    |
  | `git log --since="2026-03-01"` | filter commits by date                  |
  | `git log -p <file>`            | show file history with raw commit diffs |