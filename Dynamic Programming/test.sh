#run in terminal;   sh ./test.sh

while true; do
  ./data>testData.in
  ./1015<testData.in>1015.out
  ./ac1015<testData.in>ac1015.out
  if ! diff 1015.out ac1015.out; then
    exit 0
    echo WA
  fi
done
