print('hlelo')
check = [0x24,
0x27,
0x13,
0xC6,
0xC6,
0x13,
0x16,
0xE6,
0x47,
0xF5,
0x26,
0x96,
0x47,
0xF5,
0x46,
0x27,
0x13,
0x26,
0x26,
0xC6,
0x56,
0xF5,
0xC3,
0xC3,
0xF5,
0xE3,
0xE3,
0x0]
"""
for ( i = 0; i < 28; ++i )
  {
    if ( ((16 * a1[i]) | (a1[i] >> 4)) != check[i] )
      return 0;
  }
  return 1;
"""
word = ""
a1 = "a"*28
a1 = list(map(ord,a1))
for i in range(28):
	a1[i] = check[i]
	word += chr(((16 * a1[i]) | (a1[i] >> 4))&0xff)

print(word)
