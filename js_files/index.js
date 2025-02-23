var myInterval=setInterval(function(){
    document.getElementById("time").innerHTML=Date();
    document.getElementById("time").style.color="lightgreen";
},1000);
function addElement(){
    const list=document.getElementById("list");
    const li=document.createElement("li");
    const content=document.createTextNode("Oranges");
    li.appendChild(content);
    list.prepend(li);
};
function removeElement(){
    const list=document.getElementById("list");
    const firstChild=list.firstElementChild;
    firstChild.remove();
}
function fadeOut(){
    const box=document.getElementById("box");
    box.style.opacity=0;
}
function fadeIn(){
    const box=document.getElementById("box");
    box.style.opacity=1;
    box.style.display="block";
}
function hide(){
    const box=document.getElementById("box");
    box.style.display="none";
}
function show(){
    const box=document.getElementById("box");
    box.style.display="block";
}
function slideUp(){
    const box=document.getElementById("box");
    box.style.height="0";
}
function slideDown(){
    const box=document.getElementById("box");
    box.style.height="40vh";
}