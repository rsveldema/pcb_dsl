

for p in *.svg
do
    inkscape -D -z --export-pdf=$p.pdf -w 1024 -h 1024 $p
done

