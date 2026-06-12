# Shell
- [Snippets](#snippets)

## Links <!-- omit from toc -->


## Snippets
- **Powershell Filename String Replace:**
  ```text
  get-childitem * | foreach { rename-item -LiteralPath $_ $_.Name.Replace("Lecture ","") }
  ```