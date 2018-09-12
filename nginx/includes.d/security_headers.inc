# Headers to add additional security to built in browsers

add_header X-Frame-Options "SAMEORIGIN" always;
add_header Strict-Transport-Security "max-age=31536000; includeSubDomains";
add_header X-Xss-Protection "1; mode=block" always;
add_header Feature-Policy "geolocation none;midi none;notifications none;push none;sync-xhr none;microphone none;camera none;magnetometer none;gy$
add_header X-Content-Type-Options "nosniff" always;
add_header Referrer-Policy "no-referrer-when-downgrade";
