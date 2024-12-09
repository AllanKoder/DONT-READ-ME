# README

## Features

- Creating blogs
- Searching for blogs
- Editting blogs
- Creating users as Admin
- Highly secure
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

## Routing and Controllers
```mermaid
%%{init: {"flowchart": {"defaultRenderer": "elk"}} }%%

flowchart TD
    subgraph Views
        LoginView["Login View"]
        CreateBlogView["Create Blog View"]
        UpdateBlogView["Update Blog Confirmation"]
        BlogPostView["Blog Post View"]
        ListBlogsView["List of Blogs View"]
        SeedConfirmationView["Seed Data Confirmation View"]
    end

    subgraph Controllers
        BlogController --> CreateBlogView[Create Blog View]
        BlogController --> UpdateBlogView[Update Blog View]
        BlogController --> BlogPostView[Blog Post View]
        BlogController --> ListBlogsView[List Blogs View]
        SeedController --> SeedConfirmationView[Seed Data Confirmation View]

        LoginController --> LoginView[Login View]
        LoginController --> ListBlogsView[Login View]
    end

    subgraph Routes
        CreateUser[Create User] -->|POST + CSRF Token| LoginController
        CreateBlog[Create Blog] -->|POST + CSRF Token + Session Token| BlogController
        UpdateBlog[Update Blog] -->|POST + CSRF Token + Session Token| BlogController
        ViewBlog[View Blog] -->|GET + Session Token| BlogController
        ListBlogs[List Blogs] -->|GET + Session Token| BlogController
        UpvoteBlog[Upvote Blog] -->|POST + CSRF Token + Session Token| BlogController
        DownvoteBlog[Downvote Blog] -->|POST + CSRF Token + Session Token| BlogController
        Login[Login] -->|POST + CSRF Token| LoginController
        Logout[Logout] -->|GET + Session Token| LoginController
        SeedData[Seed Data] -->|GET + just for testing| SeedController
    end

    Controllers --> Helpers

    subgraph Helpers
        H1["Helpers/Cryptography"]
        H2["Helpers/Database"]
        H3["Helpers/Email"]
        H4["Helpers/Request"]
        H5["Helpers/Session"]
    end

```

## Used Libraries

- https://github.com/weidai11/cryptopp
- sudo apt-get install libcurl4-openssl-dev
- sudo bash < <(curl -sL https://raw.githubusercontent.com/axllent/mailpit/develop/install.sh)
- https://mariadb.com/docs/server/connect/programming-languages/cpp/install/

