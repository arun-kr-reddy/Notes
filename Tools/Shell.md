# Shell
- [Powershell](#powershell)

## Powershell
- **Filename String Replace:**
  ```sh
  get-childitem * | foreach { rename-item -LiteralPath $_ $_.Name.Replace("Lecture ","") }
  ```