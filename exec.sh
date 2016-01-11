#!/bin/bash
for i in {1..8}
do
	>&2 echo "execution $i: main dicts/dict$i queries/query$i 3 $((10#$i * 200000)) $((10#$i * 10000000)) 0.6 $((10#$i * 200000))"
	echo "execution $i: main dicts/dict$i queries/query$i 3 $((10#$i * 200000)) $((10#$i * 10000000)) 0.6 $((10#$i * 200000))"
	trie "dicts/dict$i" "queries/query$i"
	main "dicts/dict$i" "queries/query$i" 3 "$((10#$i * 200000))" "$((10#$i * 10000000))" 0.6 "$((10#$i * 200000))"
done