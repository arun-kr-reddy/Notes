# Personal
- [Job Switch](#job-switch)
- [Personal Finance](#personal-finance)
  - [Sell ESOPs on Vest](#sell-esops-on-vest)
  - [Don't Track Every Rupee](#dont-track-every-rupee)
- [ESOP Taxation](#esop-taxation)
  - [ESPP](#espp)
  - [RSU](#rsu)
  - [Tax Credit](#tax-credit)
  - [ITR Schedules](#itr-schedules)
- [Misc](#misc)

## Links <!-- omit from toc -->
- [DSA Prep I](https://www.reddit.com/r/cscareerquestions/comments/ot9ssf/comment/h6tx1vx/?utm_source=share&utm_medium=mweb3x&utm_name=mweb3xcss&utm_term=1&utm_content=share_button)
- [DSA Prep II](https://medium.com/@rajbopche/my-preparation-for-algo-ds-193c90952d8c)
- [US Stocks Taxation in India](https://www.youtube.com/watch?v=NO6OlUI1Hz4)
- [SBI TT rate](https://github.com/sahilgupta/sbi-fx-ratekeeper/blob/main/csv_files/SBI_REFERENCE_RATES_USD.csv)
- [ETrade Gain & Losses](https://us.etrade.com/etx/sp/stockplan#/myAccount/gainsLosses)
- [ETrade 1042S](https://us.etrade.com/etx/pxy/tax-center)
- [ITR Form-67](https://eportal.incometax.gov.in/iec/foservices/#/dashboard/fileIncomeTaxForm)

## To Do <!-- omit from toc -->
- [Asset Allocation](https://premium.capitalmind.in/2020/06/how-to-think-about-asset-allocation-in-india-part-2/)
- [Resume Tips](https://www.reddit.com/r/developersIndia/comments/1b401so/few_tips_to_get_your_naukri_resume_shortlisted_by/)

## Job Switch
- **When?:** can't add/update anything on your resume for 3 months
- **Leetcode Prep:**
  - if stuck for 10 min, then mark it for review, watch video solution and code it yourself
  - per problem: brief pseducode of approach, new trick/pattern, time & space complexity
  - give yourself time to forget and retry marked problems on following weekend & 3rd weekend
  - focus on understanding not memorizing, *i.e.* can you solve new problems?
  - intial prep takes multiple months, but refreshing it next time will just take weeks

## Personal Finance

### Sell ESOPs on Vest
- if you had cash, would you buy company stock?
- stock falling in future and losing your job are highly correlated
- unvested stocks & salary increments already give you exposure to company's growth

### Don't Track Every Rupee
- waste of time if already hitting your savings goal and got impulses largely under control
- energy should be spent on making money and keeping yourself healthy & happy

## ESOP Taxation
- convert INR ↔ USD using SBI TT buying rate from the last day of previous month
- check form-12B for (already-taxed) combined ESOP (RSU + ESPP) income, and tax-computation-sheet for the RSU & ESPP split

### ESPP
- `num_shares * (purchase_date_FMV - purchase_price)` is already taxed
- `num_shares * (sale_price - purchase_date_FMV)` to compute capital gains (using gain & losses page)
- ![](./Media/ESPP_Gain_Loss.png)

### RSU
- `num_shares * vest_date_FMV` is already taxed
- `num_shares * (sale_price - vest_date_FMV)` to compute capital gains (using gain & losses page)
- since one-third sold at vesting, pair automatic tax sales (STC) with your manual sale order
- ![](./Media/RSU_Gain_Loss.png)

### Tax Credit
- use form-1042S to claim 25% US dividend tax as a credit
- fill out form 67 using above values converted to INR

### ITR Schedules
- **Capital Gains:**
  - enter combined ESOP purchase & sale price
  - enter dividend under other sources
- **Foreign Source Income (FSI):** enter combined ESOP gain
- **Foreign Assets (FA):** enter combined ESOP purchase & sale price for calendar year

## Misc
- > vibecode only the things you know, or the things you don’t care about