
let rgb_raw = "255, 255, 255";

if (getUrlVars()["hsv"]) {
    let par = getUrlVars()["hsv"].split(",");
    let rgb = HSVtoRGB(par[0] / 360, par[1] / 255, par[2] / 255);

    rgb_raw = rgb.r + "," + rgb.g + "," + rgb.b;
}

$("body").css("background-color", "rgb(" + rgb_raw + ")");

const joe = colorjoe.rgb('picker', "rgb(" + rgb_raw + ")", []);
joe.on("change", function (color) {
    $("body").css("background-color", color.css());
});
joe.on("done", function (color) {
    window.location.href = "?hsv=" + Math.round(color._hue * 360) + "," + Math.round(color._saturation * 255) + "," + Math.round(color._value * 255);
});


function getUrlVars() {
    var vars = {};
    var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi,
        function (m, key, value) {
            vars[key] = value;
        });
    return vars;
}

function getWidth() {
    return Math.min(
        document.body.scrollWidth,
        document.documentElement.scrollWidth,
        document.body.offsetWidth,
        document.documentElement.offsetWidth,
        document.documentElement.clientWidth
    );
}

function HSVtoRGB(h, s, v) {
    var r, g, b, i, f, p, q, t;
    if (arguments.length === 1) {
        s = h.s, v = h.v, h = h.h;
    }
    i = Math.floor(h * 6);
    f = h * 6 - i;
    p = v * (1 - s);
    q = v * (1 - f * s);
    t = v * (1 - (1 - f) * s);
    switch (i % 6) {
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }
    return {
        r: Math.round(r * 255),
        g: Math.round(g * 255),
        b: Math.round(b * 255)
    };
}