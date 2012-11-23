list="SLEEP EAT BUILD GATHER RELAX EXPLORE COMMUNICATE WORK REALIZE_DREAM ESCAPE REPRODUCE DO_NOTHING"

for item in $list
do 
echo -n "$item\t" 
cat LOG | grep $item | wc -l  
done;
