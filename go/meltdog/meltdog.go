/*
Package meltdog implements the MELTDOG encryption. The MELTDOG is a Feistel chipher with
128 bit block size. It uses 32 bit round keys wich means that the key must be a multiple of 32 bit
or 4 bytes. The Key should be at least a 128 bit key, so that it reaches 4 rounds.
Practically MELTDOG has no Limits in key size, so you could use even 4096 bit keys (512 bytes).
*/
package meltdog

// Encrypts a block of data using the given key
func Encrypt(dst, src, key []byte) {
	var buf [32]byte // 4 x 64 bit
	L,R,T,H := buf[0:8],buf[8:16],buf[16:24],buf[24:32]
	copy(buf[:16],src)
	
	n := len(key)/4 // number of 32 bit parts of the key
	
	for i:=0 ; i<n ; i++ {
		copy(T,L)
		copy(L,R)
		feistelFunc(R,key[i*4:(i+1)*4],H)
		for j:=0 ; j<8 ; j++ { T[j]^=H[j] }
		copy(R,T)
	}
	copy(dst,buf[:16])
}

// Decrypts a block of data using the given key
func Decrypt(dst, src, key []byte) {
	var buf [32]byte // 4 x 64 bit
	L,R,T,H := buf[0:8],buf[8:16],buf[16:24],buf[24:32]
	copy(buf[:16],src)
	
	i := len(key)/4 // number of 32 bit parts of the key
	
	for i>0 {
		i--
		copy(T,R)
		copy(R,L)
		feistelFunc(L,key[i*4:(i+1)*4],H)
		for j:=0 ; j<8 ; j++ { T[j]^=H[j] }
		copy(L,T)
	}
	copy(dst,buf[:16])
}

