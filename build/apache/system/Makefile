


propfind:
	curl -i -X PROPFIND -H 'Depth: 1' http://localhost/uploads/

mkcol:
	curl -i -X MKCOL http://localhost/uploads/path/to/

curl -i -X MKCOL http://localhost/uploads/aaa/bbb/
curl -i -X MKCOL http://localhost/uploads/aaa/bbb
curl -i -X MKCOL http://localhost/uploads/aaa
curl -i -X MKCOL http://localhost/uploads/bbb/ccc
curl -i -X MKCOL http://localhost/uploads/bbb/ccc/
echo 'aaa' >  ./tmp-request-body.txt
curl -i --request PUT --data-binary @./tmp-request-body.txt http://localhost/uploads/aaa
curl -i --request PUT --data-binary @./tmp-request-body.txt http://localhost/uploads/aaa/
curl -i --request PUT --data-binary @./tmp-request-body.txt http://localhost/uploads/aaa/file.txt
echo 'aaa' >>  ./tmp-request-body.txt
curl -i --request PUT --data-binary @./tmp-request-body.txt http://localhost/uploads/aaa/file.txt
pwd

