#!/usr/bin/env python3
"""Reconcile a CSV of double-entry postings using integer minor units."""
import argparse,csv,json,sys
from collections import defaultdict
from pathlib import Path

def reconcile(path:Path)->dict:
 totals=defaultdict(int);accounts=set();count=0
 with path.open(newline="",encoding="utf-8") as stream:
  reader=csv.DictReader(stream);required={"account_id","currency","side","amount_minor"}
  if not reader.fieldnames or not required.issubset(reader.fieldnames):raise ValueError("CSV requires account_id,currency,side,amount_minor")
  for number,row in enumerate(reader,2):
   account=row["account_id"].strip();currency=row["currency"].strip();side=row["side"].strip().lower()
   try:amount=int(row["amount_minor"])
   except ValueError as exc:raise ValueError(f"line {number}: amount_minor must be integer") from exc
   if not account or len(currency)!=3 or currency.upper()!=currency or side not in {"debit","credit"} or amount<=0:raise ValueError(f"line {number}: invalid posting")
   totals[currency]+=amount if side=="debit" else -amount;accounts.add(account);count+=1
 discrepancies={k:v for k,v in sorted(totals.items()) if v}
 return {"rows":count,"accounts":len(accounts),"currency_net_minor":dict(sorted(totals.items())),"balanced":not discrepancies,"discrepancies":discrepancies}

def main()->int:
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument("csv_file",type=Path);parser.add_argument("--json",action="store_true");args=parser.parse_args()
 try:report=reconcile(args.csv_file)
 except (OSError,ValueError) as exc:print(f"reconciliation error: {exc}",file=sys.stderr);return 2
 print(json.dumps(report,indent=2) if args.json else f"rows={report['rows']} accounts={report['accounts']} balanced={report['balanced']}")
 return 0 if report["balanced"] else 1
if __name__=="__main__":raise SystemExit(main())
