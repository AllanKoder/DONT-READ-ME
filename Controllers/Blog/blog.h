#ifndef BLOG_CONTROLLER_H
#define BLOG_CONTROLLER_H

#include <memory>
#include "../../Views/views.h"

namespace Controllers
{
    /**
     * @brief Displays the page that lists all blogs.
     * 
     * Returns a View that renders the blogs page, which typically
     * includes a list of all available blog posts, with a search bar.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the blogs page.
     */
    Views::View blogsPage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Displays a specific blog post.
     * 
     * Returns a View that renders a detailed view of a single blog post,
     * identified by its ID or other parameters.
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the specific blog post.
     */
    Views::View blogPage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the upvote action for a blog post.
     * 
     * Processes an upvote request for a specified blog post and returns
     * a redirect to the blog page
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the upvote request.
     */
    Views::View upvoteBlog(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the downvote action for a blog post.
     * 
     * Processes a downvote request for a specified blog post and returns
     * a redirect to the blog page
     * 
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the downvote request.
     */
    Views::View downvoteBlog(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Displays the page for creating a new blog post.
     *
     * Returns a View that renders the form where users can enter details
     * for creating a new blog post.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the create blog page.
     */
    Views::View createBlogPage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Displays the page for updating an existing blog post.
     *
     * Returns a View that renders the form where users can edit details
     * of an existing blog post.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the update blog page.
     */
    Views::View updateBlogPage(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Handles the POST request for updating an existing blog post.
     *
     * Processes the submitted data from the update form and updates
     * the corresponding blog post in the database, returning an appropriate view afterward.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view to be rendered after processing the update request.
     */
    Views::View updateBlogPost(std::shared_ptr<cgicc::Cgicc> cgi);

    /**
     * @brief Displays the page for posting a new blog entry.
     *
     * Returns a View that renders the form where users can enter details
     * to create and submit their new blog entry.
     *
     * @param cgi Shared pointer to a Cgicc object for CGI handling.
     * @return Views::View The view representing the post blog page.
     */
    Views::View postBlogPage(std::shared_ptr<cgicc::Cgicc> cgi);
}

#endif 