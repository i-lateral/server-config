# Increase maximum submission size
client_max_body_size 100M;

location / {
    # URLs to attempt, including pretty ones.
    try_files $uri /index.php?$query_string;
}

# Handle CSS, JS, images, icons, video, audio, HTC
location ~* \.(?:css|js|jpg|jpeg|gif|png|ico|cur|gz|svg|svgz|mp4|ogg|ogv|webm|htc|woff|woff2|ttf|otf|eot)$ {
    add_header Pragma public;
    add_header Cache-Control "public";
    sendfile on;
    try_files $uri =404;
}

location ~ \.php {
    # NOTE: You should have "cgi.fix_pathinfo = 0;" in php.ini

    fastcgi_pass             unix:$socket;
    include                  /etc/nginx/fastcgi_params;
    fastcgi_param            SCRIPT_FILENAME $document_root$fastcgi_script_name;
}

# We don't need .ht files with nginx.
location ~ /\.ht {
    deny all;
}

