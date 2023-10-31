在当前文件下执行编译命令：gcc -o e3rsa e3rsa.c
生成可执行程序：e3rsa.exe

执行命令：e3rsa
生成密钥，产生文件p.txt, q.txt, n.txt, e.txt, d.txt

执行命令：e3rsa -p plainfile -n nfile -e efile -c cipherfile
（如：e3rsa -p rsa_plain.txt -n rsa_n.txt -e rsa_e.txt -c rsa_cipher.txt）
对指定明文文件（plainfile）进行数字加密，生成密文文件（cipherfile）

执行命令：e3rsa -p plainfile -n nfile -e efile -c cipherfile
（如：e3rsa -p rsa_plain.txt -n rsa_n.txt -d rsa_d.txt -c rsa_sign.txt）
对指定明文文件（plainfile）进行数字签名，生成签名文件（cipherfile）