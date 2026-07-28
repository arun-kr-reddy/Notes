# Taxation
- [Abbreviations](#abbreviations)
- [Pre-Requisites](#pre-requisites)
- [Schedules](#schedules)

## Links <!-- omit from toc -->
- [US Stocks Taxation in India](https://www.youtube.com/watch?v=NO6OlUI1Hz4)

## Abbreviations
- ㅤ
  |       |                                               |
  | ----- | --------------------------------------------- |
  | CY    | Calendar Year                                 |
  | FY    | Financial Year                                |
  | CG    | Capital Gains                                 |
  | FA    | Foreign Assets                                |
  | OS    | Income from Other Sources                     |
  | CY+FY | 15 month merged CY + FY (`Jan 1` to `Mar 31`) |
  | FMV   | Fair Market Value (is already taxed)          |

## Pre-Requisites
- **Income Tax Department:**
  - Annual Information Statement (AIS)
  - Taxpayer Information Summary (TIS)
- **Workplace:**
  - Form 16 (A & B)
  - Form 12BA
  - Tax Computation Sheet for March
- **Domestic Capital Gains:**
  - MFCentral FY Consolidated Capital Gains Statement
- **International Capital Gains:**
  - [IKBR Activity Statement](https://www.interactivebrokers.co.in/AccountManagement/AmAuthentication?action=RM_STATEMENTS) for CY+FY
  - [IKBR Trade Confirmations](https://www.interactivebrokers.co.in/AccountManagement/AmAuthentication?action=RM_STATEMENTS) for CY+FY
  - [ETrade Gain/Loss Report](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses) for CY+FY
  - [ETrade Monthly Statements](https://us.etrade.com/etx/pxy/accountdocs?inav=nav:documents#/documents) for CY+FY
  - **note:** Form 1042S is for CY, only downloades as extra proof

### Reconcile International
- create CY+FY ledger mapping all stock vesting to sales
  - FY will be used for schedule CG
  - CY will be used for schedule FA sale proceeds
  - **note:** ensure Gain/Loss report is showing FMV as buy price
- additionally use monthly statements for:
  - **Schedule FA:**
    - get unsold shares on 31st Dec for closing value
    - calculate peak holding value during CY
  - **Schedule OS:** log different dividends received (& tax withholdings) during FY along with date
  - search for these keywords in ETrade monthly reports: `Cash, BDP, MMFs`, `Stocks`, `Qualified Dividends`, `Tax Withholdings`  
  ![](./Media/ETrade%20Monthly%20Statement.png)
- use previous month's last day's [SBI `TT BUY` rate](https://github.com/sahilgupta/sbi-fx-ratekeeper/blob/main/csv_files/SBI_REFERENCE_RATES_USD.csv) for USD -> INR conversion

### Tax Credit
- `e-File` -> `Income Tax Forms` -> `File Income Tax Forms` -> `Double Taxation Relief (Form 67)`
- ㅤ
  |                               |                         |
  | ----------------------------- | ----------------------- |
  | country                       | US                      |
  | source of income              | dividend                |
  | amount                        | from monthly sheet      |
  | tax paid                      | from monthly sheet      |
  | tax paid %                    | 25%                     |
  | tax payable normal provisions | 30% of amount           |
  | tax payable 115JB/JC          | 0 (business deductions) |
  | article number                | 10 (per country)        |
  | tax rate as per DTAA          | 25 (per country)        |
  | amount                        | = tax paid              |

## Schedules

### Salary
- Verify Salary & Tax Deducted from Form 16B
- Verify Base Salary & ESOPs split from March Tax Computation Sheet

### Capital Gains
- **Long Term Holding Period:**
  |                           |                          |
  | ------------------------- | ------------------------ |
  | domestic equity           | > 1 year                 |
  | domestic debt             | never, always short term |
  | international debt/equity | > 2 years                |
- **Short Term CG:**
  - **`2.`:** domestic equity
  - **`5.`:** combined domestic debt + international
- **Long Term CG:**
  - **`3.`:** domestic equity
  - **`8.`:** international
- **note:** extra advance tax interest levied if quarterly breakup not filled
- **note:** always check net gain, usually higher than net outflow due to STT deductions

### Other Sources
- interest income is auto-filled, verify against AIS
- fill all dividends (domestic + international) in `1.`, and its quarterly breakup in `10.`
- **note:** extra advance tax interest levied if quarterly breakup not filled

### Special Income
- verify entries with special tax rates
- short term debt & short term international not listed since taxed at slab rate

### Foreign Source of Income
- ㅤ
  |                           |                        |
  | ------------------------- | ---------------------- |
  | country                   | US                     |
  | capital gains income      | from monthly sheet     |
  | capital gains tax paid    | 0                      |
  | capital gains tax payable | 30% of CG income       |
  | dividend income           | from monthly sheet     |
  | dividend tax paid         | from monthly sheet     |
  | dividend tax payable      | 30% of dividend income |
  | DTAA article number       | 10 (per country)       |

### Tax Relief
- verify withholden dividend tax
- use `90` section for TDAA countries, `No` for if tax credited by foreign tax authority

### Foreign Assets
- **Custodial Accounts (`A2`):** add cash details from ETrade & IKBR in separate rows
- **Equity (`A3`):** add equity/debt details from ETrade & IKBR, one ticker per row