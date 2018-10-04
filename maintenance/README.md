# Basic maintenanance page

This is a simple HTML page to display when a site goes down for maintenance.

## Usage on NGINX

On an nginx server you will need to setup your server config for a project to
expect the maintanence page. Do this by adding the following to the inside of
your "server" block (within the site's config file).

    ##################################
    # MAINTENENCE
    #
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
    # END MAINTENANCE
    ###################################

Once you have done this, simply copy the index.html file from this repo to a
file named 503.html within the project root.

    # cp maintanence/index.html project-folder/503.html

This config will then make the site unavailable to all visitors except those
visiting via the IP 84.9.132.84
