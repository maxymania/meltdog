package meltdog

import "fmt"
import "crypto/cipher"

type KeySizeError int
func (k KeySizeError) Error() string { return fmt.Sprint("KeySizeError:",int(k)) }

type mtblock struct{
	key []byte
}

// The key argument must be a multiple of 4, so that len(key)%4 == 0
func New(key []byte) (cipher.Block,error) {
	l := len(key)
	if (l%4) != 0 {
		return nil,KeySizeError(l)
	}
	return &mtblock{key},nil
}

func (m *mtblock) BlockSize() int { return 16 }
func (m *mtblock) Encrypt(dst, src []byte) { Encrypt(dst,src,m.key) }
func (m *mtblock) Decrypt(dst, src []byte) { Decrypt(dst,src,m.key) }
