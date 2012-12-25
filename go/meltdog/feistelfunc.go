package meltdog

var i8 = []int{2,6,5,4,7,1,0,3}
var i4 = []int{1,3,0,2}
var bvec = []byte{84, 87, 81, 93, 186, 138, 234, 42}

// The Feistel-Function of MELTDOG
func feistelFunc(d,k, dbuf []byte) {
	var kbuf [4]byte
	var i,j int

	d2k:= int(d[0]^d[1]^d[2]^d[3]^d[4]^d[5]^d[6]^d[7])
	d2k = (d2k^(d2k>>4))
	d2k = (d2k^(d2k>>2))&3

	k2k:= int(k[0]^k[1]^k[2]^k[3])
	k2k = (k2k^(k2k>>4))
	k2k = (k2k^(k2k>>2))&3

	d2d:= int(d[0]^d[1]^d[2]^d[3]^d[4]^d[5]^d[6]^d[7])
	d2d = (d2d^(d2d>>3)^(d2d>>6))&7

	k2d:= int(k[0]^k[1]^k[2]^k[3])
	k2d = (k2d^(k2d>>3)^(k2d>>6))&7
	for i=0 ; i<4 ; i++ {
		j = i4[i^d2k]^k2k
		kbuf[i] = k[j]
		j = i4[j^k2k]^d2k
		kbuf[i] ^= bvec[j]
	}
	for i=0 ; i<8 ; i++ {
		j = i8[i^k2d]^d2d
		dbuf[i] = d[j]
		j = i8[j^k2d]^d2d
		dbuf[i] ^= bvec[j]
		j = i8[j]
		dbuf[i] ^= kbuf[j&3]
	}
}
