# Drupal single site rules.
# Designed to be included in any server {} block.

index index.php;

location = /favicon.ico {
    log_not_found off;
    access_log off;
}

location = /robots.txt {
    allow all;
    log_not_found off;
    access_log off;
}

# Very rarely should these ever be accessed outside of your lan
location ~* \.(txt|log)$ {
    allow 192.168.0.0/16;
    deny all;
}

location ~ \..*/.*\.php$ {
    return 403;
}

location ~ ^/sites/.*/private/ {
    return 403;
}

# Block access to scripts in site files directory
location ~ ^/sites/[^/]+/files/.*\.php$ {
    deny all;
}

# Allow "Well-Known URIs" as per RFC 5785
location ~* ^/.well-known/ {
    allow all;
}

# Block access to "hidden" files and directories whose names begin with a
# period. This includes directories used by version control systems such
# as Subversion or Git to store control files.
location ~ (^|/)\. {
    return 403;
}

location / {
    try_files $uri /index.php?$query_string; # For Drupal >= 7
}

location @rewrite {
    rewrite ^/(.*)$ /index.php?q=$1;
}

# Don't allow direct access to PHP files in the vendor directory.
location ~ /vendor/.*\.php$ {
    deny all;
    return 404;
}

location ~ \.php$ {
    fastcgi_split_path_info ^(.+?\.php)(|/.*)$;
    fastcgi_buffer_size 32k;
    fastcgi_busy_buffers_size 64k;
    fastcgi_buffers 4 32k;
    fastcgi_keep_conn on;

    include        fastcgi_params;
    fastcgi_pass   unix:$socket;
    fastcgi_index  index.php;
    fastcgi_param  SCRIPT_FILENAME $document_root$fastcgi_script_name;
    fastcgi_param PATH_INFO $fastcgi_path_info;
    fastcgi_param QUERY_STRING $query_string;
    fastcgi_intercept_errors on;
}

# Fighting with Styles? This little gem is amazing.
# location ~ ^/sites/.*/files/imagecache/ { # For Drupal <= 6
location ~ ^/sites/.*/files/styles/ { # For Drupal >= 7
    try_files $uri @rewrite;
}

# Handle private files through Drupal. Private file's path can come
# with a language prefix.
location ~ ^(/[a-z\-]+)?/system/files/ { # For Drupal >= 7
    try_files $uri /index.php?$query_string;
}

location ~* \.(js|css|png|jpg|jpeg|gif|ico|svg)$ {
    try_files $uri @rewrite;
    expires max;
    log_not_found off;
}

