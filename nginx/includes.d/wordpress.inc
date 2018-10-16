# WordPress single site rules.
# Designed to be included in any server {} block.

# Deny all attempts to access hidden files such as .htaccess, .htpasswd, .DS_Store (Mac).
# Keep logging the requests to parse later (or to pass to firewall utilities such as fail2ban)
location ~ /\. {
        deny all;
}

# Deny access to any files with a .php extension in the uploads directory
# Works in sub-directory installs and also in multisite network
# Keep logging the requests to parse later (or to pass to firewall utilities such as fail2ban)
location ~* /(?:uploads|files)/.*\.php$ {
        deny all;
}

# This order might seem weird - this is attempted to match last if rules below fail.
# http://wiki.nginx.org/HttpCoreModule
location / {
	try_files $uri $uri/ /index.php?$args;
}

# Add trailing slash to */wp-admin requests.
rewrite /wp-admin$ $scheme://$host$uri/ permanent;

# Directives to send expires headers and turn off 404 error logging.
location ~* ^.+\.(ogg|ogv|svg|svgz|eot|otf|woff|mp4|ttf|rss|atom|jpg|jpeg|gif|png|ico|zip|tgz|gz|rar|bz2|doc|xls|exe|p$
    access_log off;
    log_not_found off;
    expires max;
    add_header Cache-Control "public";
}

# Cache all CSS and JS
location ~* \.(?:css|js)$ {
    expires 48h;
    access_log off;
    add_header Cache-Control "public";
}

# Uncomment one of the lines below for the appropriate caching plugin (if used).
#include global/wordpress-wp-super-cache.conf;
#include global/wordpress-w3-total-cache.conf;

# Pass all .php files onto a php-fpm/php-fcgi server.
location ~ [^/]\.php(/|$) {
    fastcgi_split_path_info ^(.+?\.php)(/.*)$;
    if (!-f $document_root$fastcgi_script_name) {
        return 404;
    }

    # This is a robust solution for path info security issue and works with "cgi.fix_pathinfo = 1" in /etc/php.ini (de$
    include fastcgi_params;
    fastcgi_pass   unix:$socket;
    fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
}

# Enable GZIP compression for relevent files
# Thanks to this post for the example:
# https://stackoverflow.com/questions/12640014/enable-gzip-for-css-and-js-files-on-nginx-server-for-magento#12644530
gzip on;
gzip_disable "msie6";

gzip_comp_level 6;
gzip_min_length 1100;
gzip_buffers 16 8k;
gzip_proxied any;
gzip_types
    text/plain
    text/css
    text/js
    text/xml
    text/javascript
    application/javascript
    application/x-javascript
    application/json
    application/xml
    application/rss+xml
    image/svg+xml;

