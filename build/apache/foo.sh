#!/bin/bash


case $1 in
"propfind")
  cmd="curl --include --request PROPFIND "
  cmd="$cmd --header 'Depth: 1' "
  cmd="$cmd http://localhost:18080/uploads/"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"propfind-nodepth")
  cmd="curl --include --request PROPFIND "
  cmd="$cmd http://localhost:18080/uploads/"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"mkcol-1")
  cmd="curl --include --request MKCOL "
  cmd="$cmd http://localhost:18080/abcd/"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"mkcol")
  cmd="curl --include --request MKCOL "
  cmd="$cmd http://localhost:18080/uploads/abcd/"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"upload-dir")
  echo 'aaa' >  ./test.txt
  echo 'bbb' >> ./test.txt

  cmd="curl --include --request PUT "
  cmd="$cmd --data-binary @./test.txt "
  cmd="$cmd http://localhost:18080/uploads/"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"upload")
  echo 'aaa' >  ./test.txt
  echo 'bbb' >> ./test.txt

  cmd="curl --include --request PUT "
  cmd="$cmd --data-binary @./test.txt "
  cmd="$cmd http://localhost:18080/uploads/test.txt"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

esac

exit 0

