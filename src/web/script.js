const joe = colorjoe.rgb('picker', "rgb(" + getUrlVars()["rgb"] + ")", []);
joe.on("change", function (color) {
    $("body").css("background-color", color.css());
});
joe.on("done", function (color) {
    window.location.href = "?rgb=" + color.css().replace(/ /g, "").replace("rgb(", "").replace(")", "");
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

$("body").css("background-color", "rgb(" + getUrlVars()["rgb"] + ")");