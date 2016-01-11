#!/bin/bash
mkdir -p dicts
mkdir -p queries
for i in {1..8}
do
	echo "generating dict$i with $((10#$i * 1000000)) elements"
    python rand.py "dicts/dict$i" "$((10#$i * 1000000))"
    echo "generating query$i with $((10#$i * 100000)) elements"
	python rand.py "dicts/dict$i" "queries/query$i" "$((10#$i * 100000))" 50
done
