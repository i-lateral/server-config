# Settings to use for a Silverstripe install in Nginx
client_max_body_size 0; # Manage this in php.ini (upload_max_filesize & post_max_size);

# Defend against SS-2015-013 -- http://www.silverstripe.org/software/download/security-releases/ss-2015-013
if ($http_x_forwarded_host) {
    return 400;
}

location / {
    try_files $uri /index.php?$query_string;
}

error_page 404 /assets/error-404.html;
error_page 500 /assets/error-500.html;
error_page 502 /assets/error-500.html;
error_page 503 /assets/error-500.html;

# Cache all Media: images, icons, video, audio, HTC
location ~* \.(?:jpg|jpeg|gif|png|ico|cur|gz|svg|svgz|mp4|ogg|ogv|webm|htc|woff|woff2|ttf|otf|eot)$ {
    expires 1y;
    access_log off;
    add_header Pragma public;
    add_header Cache-Control "public";
    sendfile on;
    try_files $uri =404;
}

# Cache all CSS and JS
location ~* \.(?:css|js)$ {
    expires 1w;
    access_log off;
    add_header Pragma public;
    add_header Cache-Control "public";
    sendfile on;
    try_files $uri =404;
}

location ^~ /assets/ {
    expires 1y;
    access_log off;
    add_header Pragma public;
    add_header Cache-Control "public";
    sendfile on;
    try_files $uri =404;
}

location /index.php {
    fastcgi_buffer_size 32k;
    fastcgi_busy_buffers_size 64k;
    fastcgi_buffers 4 32k;
    fastcgi_keep_conn on;

    include        fastcgi_params;
    fastcgi_pass   unix:$socket;
    fastcgi_index  index.php;
    fastcgi_param  SCRIPT_FILENAME $document_root$fastcgi_script_name;
}

location ~ /\.. {
    deny all;
}

location ~ \.ss$ {
    satisfy any;
    allow 127.0.0.1;
    deny all;
}

location ~ web\.config$ {
    deny all;
}

location ~ \.ya?ml$ {
    deny all;
}

location ^~ /vendor/ {
    deny all;
}

location ~* /silverstripe-cache/ {
    deny all;
}

location ~* composer\.(json|lock)$ {
    deny all;
}

