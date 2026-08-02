# Shell
- [Powershell Filename String Replace](#powershell-filename-string-replace)

## Powershell Filename String Replace
- ㅤ
  ```text
  get-childitem * | foreach { rename-item -LiteralPath $_ $_.Name.Replace("Lecture ","") }
  ```