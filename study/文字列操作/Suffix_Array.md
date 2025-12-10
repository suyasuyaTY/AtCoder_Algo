# Suffix_Arrayとlcp_array

## Suffix_Array

### 概要
接尾辞をsortした時の順番を、接尾辞の開始のところから記録したもの。
```text
 0 mmiissiissiippii$
 1 miissiissiippii$
 2 iissiissiippii$
 3 issiissiippii$
 4 ssiissiippii$
 5 siissiippii$
 6 iissiippii$
 7 issiippii$
 8 ssiippii$
 9 siippii$
10 iippii$
11 ippii$
12 ppii$
13 pii$
14 ii$
15 i$
16 $
```

suffix_array は左側の数字が入っている。
```text
16 $
15 i$
14 ii$
10 iippii$
 6 iissiippii$
 2 iissiissiippii$
11 ippii$
 7 issiippii$
 3 issiissiippii$
 1 miissiissiippii$
 0 mmiissiissiippii$
13 pii$
12 ppii$
 9 siippii$
 5 siissiippii$
 8 ssiippii$
 4 ssiissiippii$
```

### アルゴリズム


### 参考文献
[まめメモ](https://mametter.hatenablog.com/entry/20180130/p1)