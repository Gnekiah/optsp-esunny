#!/bin/bash
git log --date=iso --pretty=format:%ad,%an,%h,%s > commit-log.csv
