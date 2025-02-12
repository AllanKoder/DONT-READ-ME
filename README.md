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

