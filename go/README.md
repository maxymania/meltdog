# Implementation in go

Just copy the folder 'meltdog' into your src directory.

It Implements these Three Functions.

```
func Decrypt(dst, src, key []byte)
    Decrypts a block of data using the given key

func Encrypt(dst, src, key []byte)
    Encrypts a block of data using the given key

func New(key []byte) (cipher.Block, error)
    Creates an cipher.Block instance for MELTDOG encryption.
    The key argument must be a multiple of 4, so that len(key)%4 == 0
```

