#include <pgmspace.h>

// #ifndef SECRETS_HPP
// #define SECRETS_HPP

const char MQTT_HOST[] = "<>>.amazonaws.com";

// Copy contents from  AmazonRootCAX.pem here ▼
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----


















-----END CERTIFICATE-----
)EOF";

// Copy contents from  XXXXXXXX-certificate.pem.key here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----

















-----END CERTIFICATE-----
)KEY";

// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----

























-----END RSA PRIVATE KEY-----
)KEY";

// #endif