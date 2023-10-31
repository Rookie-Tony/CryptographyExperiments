目录A为发送方，目录B为接收方
目录lib下是一些自己编写的函数，请勿修改

对源文件进行编译链接生成可执行程序时：
Windows系统执行：mingw32-make 程序名(enORde/key/verify)
Linux系统执行：make 程序名(enORde/key/verify)

程序使用说明：
enORde.exe:
DES加密:	enORde -des -en 明文文件 密钥文件 指定密文文件（不存在则新建，存在则覆盖）
DES解密:	enORde -des -de 密文文件 密钥文件 指定明文文件（不存在则新建，存在则覆盖）
RSA加密:	enORde -rsa -en 明文文件 公钥n文件 公钥e文件 指定密文文件（不存在则新建，存在则覆盖）
RSA解密:	enORde -rsa -de 密文文件 私钥n文件 私钥d文件 指定明文文件（不存在则新建，存在则覆盖）
sha256:	enORde -sha256 明文文件 指定写入文件（不存在则新建，存在则覆盖）

key.exe:
生成DES密钥:	key -des 文件名（不存在则新建，存在则覆盖）
生成RSA密钥:	key -rsa n文件 e文件 d文件（均为不存在则新建，存在则覆盖）

verify.exe:
验证数字签名：	verify -ver 签名文件 恢复明文文件 发送方公钥n 发送方公钥e