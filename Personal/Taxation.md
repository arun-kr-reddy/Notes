# Taxation
- [Abbreviations](#abbreviations)
- [Pre-Requisites](#pre-requisites)
- [Reconcile International](#reconcile-international)
- [Tax Credit](#tax-credit)
- [Schedules](#schedules)
- [Calculate Indian Mutual Funds \& Domestic Equity (Schedule CG)](#calculate-indian-mutual-funds--domestic-equity-schedule-cg)
- [Calculate US Stock \& Foreign ETF Gains (Schedule CG)](#calculate-us-stock--foreign-etf-gains-schedule-cg)
- [Declare Foreign Assets (Schedule FA)](#declare-foreign-assets-schedule-fa)
- [Declare Assets \& Liabilities (Schedule AL)](#declare-assets--liabilities-schedule-al)
- [Claim Foreign Tax Credit (Schedule FSI / TR \& Form 67)](#claim-foreign-tax-credit-schedule-fsi--tr--form-67)
- [Verify \& File ITR-2](#verify--file-itr-2)

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
- **Domestic Capital Gains:**
  - MFCentral FY Consolidated Capital Gains Statement
- **International Capital Gains:**
  - [IKBR Activity Statement](https://www.interactivebrokers.co.in/AccountManagement/AmAuthentication?action=RM_STATEMENTS) for CY+FY
  - [IKBR Trade Confirmations](https://www.interactivebrokers.co.in/AccountManagement/AmAuthentication?action=RM_STATEMENTS) for CY+FY
  - [ETrade Gain/Loss Report](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses) for CY+FY
  - [ETrade Monthly Statements](https://us.etrade.com/etx/pxy/accountdocs?inav=nav:documents#/documents) for CY+FY
  - **note:** Form 1042S is for CY, instead use monthly statements

## Reconcile International
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
- use previous month's last day's [SBI `TT BUY` rate](https://github.com/sahilgupta/sbi-fx-ratekeeper/blob/main/csv_files/SBI_REFERENCE_RATES_USD.csv) for USD -> INR conversion

## Tax Credit
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
Income Schedules: Salary, Capital Gains (CG), Income from Other Sources (OS), Schedule 112A.
Foreign & Tax Credit Schedules: Foreign Assets (FA), Foreign Source Income (FSI), Tax Relief (TR).

### Salary
- Verify Salary & Tax Deducted from Form 16B

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
- **note:** always check actual gain, which is higher than net outflow amount due to STT deductions

### Other Sources
- interest income is auto-filled, verify against AIS
- fill all dividends (domestic + international) in `1.`, and its quarterly breakup in `10.`
- **note:** advance tax levied if quarterly breakup not filled

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

## Calculate Indian Mutual Funds & Domestic Equity (Schedule CG)

* **Arbitrage Funds (Held < 12 months):**
* Classified as Short-Term Capital Gains (STCG)
* Tax Rate: **20%** (Section 111A)


* **International Mutual Funds (Held > 24 months):**
* Classified as Long-Term Capital Gains (LTCG)
* Tax Rate: **12.5%** (without indexation)


* **Domestic Equity (Held > 12 months):**
* Classified as LTCG
* Tax Rate: **12.5%** on aggregate equity gains exceeding **₹1.25 Lakhs** per year



---

## Calculate US Stock & Foreign ETF Gains (Schedule CG)

* **Cost Basis:**
* Fair Market Value (FMV) on vest/purchase date converted to INR using SBI TTBR


* **Holding Periods & Rates (QCOM Shares):**
* Held ≤ 24 months: **STCG** taxed at your **income slab rate**
* Held > 24 months: **LTCG** taxed at **12.5%** (without indexation)



---

## Declare Foreign Assets (Schedule FA)

* **Reporting Period:**
* **Calendar Year** (Jan 1 to Dec 31)


* **What to Declare:**
* **Table A3:** E*TRADE QCOM shares (peak value, closing value, acquisition cost)
* **Table A1 / A2:** IBKR account cash balance & IB01 UCITS ETF holdings
* **Table G:** Any foreign dividends or yield earned


* **Rules:**
* Convert all USD values to INR using the relevant month-end SBI TTBR


* **Penalty:**
* **Missing or incorrect disclosures trigger a ₹10 Lakh fine** under the Black Money Act



---

## Declare Assets & Liabilities (Schedule AL)

* **Criteria:**
* Mandatory because total income exceeds **₹50 Lakhs**


* **Items to List (Cost Price as of March 31):**
* Immovable property (Land, house)
* Financial assets (Bank balances, Indian MFs, QCOM stock, IB01 ETF)
* Movable assets (Vehicles, gold/jewelry, cash in hand)
* Related liabilities (Home loans, personal loans)



---

## Claim Foreign Tax Credit (Schedule FSI / TR & Form 67)

* **Setup:**
* Check for US tax withheld at source (e.g., 25% TDS on QCOM dividends)


* **Mandatory Action:**
* File **Form 67 online BEFORE filing ITR-2** to claim Foreign Tax Credit (FTC) under DTAA
* Input foreign tax paid in Schedule FSI and Schedule TR



---

## Verify & File ITR-2

* Compute total taxable income and pay any due self-assessment tax
* Submit your ITR-2 form on the Income Tax e-filing portal
* E-verify electronically (e.g., via Aadhaar OTP or Net Banking) within 30 days