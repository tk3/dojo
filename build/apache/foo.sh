#!/bin/bash

webdav_url="http://localhost:18080/uploads/"

case $1 in
"propfind")
  cmd="curl --include --request PROPFIND "
  cmd="$cmd --header 'Depth: 1' "
  cmd="$cmd $webdav_url"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"propfind-allprop")
  body=./tmp-request-body.txt
  echo '<?xml version="1.0" encoding="utf-8" ?>' >  $body
  echo '<D:propfind xmlns:D="DAV:">'             >> $body
  echo '<D:allprop/>'                            >> $body
  echo '</D:propfind>'                           >> $body

  cmd="curl --include --request PROPFIND "
  cmd="$cmd --header 'Depth: 1' "
  cmd="$cmd --data-binary @$body "
  cmd="$cmd $webdav_url"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"propfind-nodepth")
  cmd="curl --include --request PROPFIND "
  cmd="$cmd $webdav_url"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"proppatch")
  body=./tmp-request-body.txt
  echo '<?xml version="1.0" encoding="utf-8" ?>' >  $body
  echo '<D:propertyupdate xmlns:D="DAV:" xmlns:Z="http://ns.example.com/standards/z39.50/">'  >> $body
  echo '<D:set>'                             >> $body
  echo '<D:prop>'                            >> $body
  echo '<Z:Authors>'                         >> $body
  echo '<Z:Author>Jim Whitehead</Z:Author>'  >> $body
# echo '<Z:Author>Roy Fielding</Z:Author>'   >> $body
  echo '</Z:Authors>'                        >> $body
  echo '</D:prop>'                           >> $body
  echo '</D:set>'                            >> $body
# echo '<D:remove>'                          >> $body
# echo '<D:prop>'                            >> $body
# echo '<Z:Copyright-Owner/>'                >> $body
# echo '</D:prop>'                           >> $body
# echo '</D:remove>'                         >> $body
  echo '</D:propertyupdate>'                 >> $body

  cmd="curl --include --request PROPPATCH "
  cmd="$cmd --header \"Content-Type: application/xml; charset=\"utf-8\"\" "
  cmd="$cmd --data-binary @$body "
  cmd="$cmd ${webdav_url}test.txt"

  echo $cmd
  $SHELL -c "$cmd"

  echo "========"

  cmd="curl --include --request PROPFIND "
  cmd="$cmd --header 'Depth: 1' "
  cmd="$cmd ${webdav_url}test.txt"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"mkcol-1")
  cmd="curl --include --request MKCOL "
  cmd="$cmd ${webdav_url}abcd"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"mkcol")
  cmd="curl --include --request MKCOL "
  cmd="$cmd ${webdav_url}abcd"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"put-dir")
  body=./tmp-request-body.txt
  echo 'aaa' >  $body
  echo 'bbb' >> $body

  cmd="curl --include --request PUT "
  cmd="$cmd --data-binary @$body "
  cmd="$cmd ${webdav_url}"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

"put")
  body=./tmp-request-body.txt
  echo 'aaa' >  $body
  echo 'bbb' >> $body

  cmd="curl --include --request PUT "
  cmd="$cmd --data-binary @$body "
  cmd="$cmd ${webdav_url}test.txt"

  echo $cmd
  $SHELL -c "$cmd"
  ;;

*)
  echo "not supported. [$1]"
  ;;

esac

exit 0

