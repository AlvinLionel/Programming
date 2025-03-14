var myInterval = setInterval(function () {
    document.getElementById("time").innerHTML = Date();
    document.getElementById("time").style.color = "lightgreen";
}, 1000);
var randomNUm=setInterval(function (){
    document.getElementById("demo").innerHTML=Math.random()*100000000;
},500)