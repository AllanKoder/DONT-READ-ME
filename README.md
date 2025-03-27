# DONT README

DON'T README is a pretty average and boring blogging site, your usual stuff. But, it was a nice chance to explore what goes into making a web framework, and the security aspects as well.

## Features

- Creating blogs
- Searching for blogs with HTMX
- Editting blogs
- Creating users as Admin Only
- Highly secure Auth Tokens
- Login with MFA2 (Email, and Authentication App)
- CSRF protection
- Sliding expiration session

# Images
_Homepage:_<br>
![image](https://github.com/user-attachments/assets/a431f746-a0ae-4d3c-a852-c4deb9d0509b)

<br>

_Creating a Blog:_<br>
![image](https://github.com/user-attachments/assets/9d7858b7-eb2d-4971-898e-cc558aee0ac7)

<br>

_2-MFA:_<br>
![image](https://github.com/user-attachments/assets/2bfb5275-169b-4a1c-80a3-1975f1e2dbea)

<br>

_3-MFA (if Admin):_<br>
![image](https://github.com/user-attachments/assets/bbf69ba3-c64a-466b-8b04-2af432359b0e)

## High-level Blog Architecture

```mermaid
flowchart TD
    A["User<br>(A user of the application<br>who can create and <br>manage blog posts)"] -->|Uses| B["Web Server<br>(Handles HTTP requests<br>and serves static<br>content)"]
    C["Admin<br>(An administrator who can<br>manage users<br>and blog posts)"] -->|Uses| B
    B -->|Forwards requests to| D["CGI Application<br>(Processes business logic)"]
    D -->|Reads from and writes to| E["Database<br>(Stores user<br>and blog data)"]
    D -->|Uses cryptography functions| F["Cryptography Library<br>(Performs Cryptographic<br>Functions)"]
    D -->|Sends notifications to| G["Email Service<br>(Handles email<br>notifications for user<br>actions)"]
```

## Used Libraries

- CryptoPP
    - https://github.com/weidai11/cryptopp
- Libcurl
    - sudo apt-get install libcurl4-openssl-dev

- Maria DB 
    - https://mariadb.com/docs/server/connect/programming-languages/cpp/install/

