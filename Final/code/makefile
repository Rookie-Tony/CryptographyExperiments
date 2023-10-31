enORde:
	gcc enORde.c lib/encrypt.c lib/fileRW.c lib/DES.c lib/RSA.c lib/sha256.c -o enORde

key: 
	gcc key.c lib/RSA.c -o key

verify:
	gcc verify.c lib/encrypt.c lib/fileRW.c lib/DES.c lib/RSA.c lib/sha256.c -o verify

clean:
	del *.o *.exe -rf