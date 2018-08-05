var t=1;
window.onload=function(){
    var websock = new WebSocket('ws://' + window.location.hostname + ':81/');
    websock.onopen = function(evt) { console.log('websock open'); };
    websock.onclose = function(evt) { console.log('websock close'); };
    websock.onerror = function(evt) { console.log(evt); };
    var list=document.querySelectorAll(".rbtn");
     function msg_1(el){
            el.target.style.backgroundColor="red";
            websock.send(el.target.innerText);
    }
    function msg_2(el){
        el.target.style.backgroundColor="#38e05e";
        if(el.target.innerText=='L' || el.target.innerText=='R' || el.target.innerText=='U' ||el.target.innerText=='D' ){
            websock.send("stop");
        }
    }
    list.forEach(function(el){
        el.addEventListener('touchstart',msg_1,false);
        el.addEventListener('touchend',msg_2,false);
    });
    var claw=document.querySelector(".claw");
    claw.addEventListener('touchstart',hold,false);
    function hold(el){
       if(t%2==1){
        el.target.style.backgroundColor='#ea8213';
        websock.send("close");
        t++;
       }else{
        el.target.style.backgroundColor="#f5d21f";
        websock.send("open");
        t++;
       }
}

}