# Config Settings for putting a site into maintenance
# Simply add a 503.html file to the root of your project
# and the site will go into maintenance
set $maint_exists 0;
set $maint_allow 1;
if (-f $document_root/503.html) {
    set $maint_exists 1;
}
if ( $remote_addr != "84.9.132.84" ) {
    set $maint_allow 0$maint_exists;
}
if ( $maint_allow = 01 ) {
    return 503;
}
error_page 503 @maintenance;
location @maintenance {
    rewrite ^(.*)$ /503.html break;
}
