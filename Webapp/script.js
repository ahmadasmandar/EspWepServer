// Initialize Firebase
//The project has been deleted in firebase
//fill in your own config info 
// var firebaseConfig = {
//   apiKey: "AIzaSyB3llw-duS5ucD5TyDP6JNiBP3ta4AwGWs",
//   authDomain: "esptut-88be5.firebaseapp.com",
//   databaseURL: "https://esptut-88be5.firebaseio.com",
//   projectId: "esptut-88be5",
//   storageBucket: "esptut-88be5.appspot.com",
//   messagingSenderId: "1087808364492",
//   appId: "1:1087808364492:web:b0aa09b257f885fb158769"
// };
// Initialize Firebase
// firebase.initializeApp(firebaseConfig);


// $(document).ready(function () {
//   var database = firebase.database();
//   var ledStatus;
//   var readName;
//   // read the value of a key 
//   database.ref().on("value", getLedStatue);
//   // end of reading and changing the value of the h1 class
//   function getLedStatue(snap) {
//     ledStatus = snap.val().ledStatus;

//     if (ledStatus == 1) {
//       $("#lighstat").text("The light is on");
//     } else {
//       $("#lighstat").text("The light is off");
//     }
//   }
//   $("#clickme").on('click', function () {
//     var firebaseRef = firebase.database().ref().child("ledStatus");

//     if (ledStatus == 1) {
//       // set the new values
//       firebaseRef.set(0);
//       ledStatus = 0;
//     } else {
//       // set the new values
//       firebaseRef.set(1);
//       ledStatus = 1;
//     }
//   });

//   $("#second").on('click', function () {
//     // read the value of a key 
//     database.ref().on("value", function (snap) {
//       readName = snap.val().name
//     });
//     // get the name of the child to make ready to change
//     var firebaseRef = firebase.database().ref().child("name");
//     if (readName == "Hallo i am true") {
//       // set the new values
//       firebaseRef.set("Hallo I am  flase");
//     } else {
//       firebaseRef.set("Hallo i am true");
//     }

//   });
//   $("#success").on("click", printHello);

//   function printHello() {
//     alert("Hello World!");
//   }
// });

// document.querySelector("#success").addEventListener("click",printHello);
const Http = new XMLHttpRequest();

document.querySelector("#clickme").addEventListener("click", turn_on);
document.querySelector("#second").addEventListener("click", turn_off);

function turn_on() {
  const url = 'http://192.168.0.104/on';
  var request = new XMLHttpRequest();
  request.open('GET', url);
  request.responseType = 'text';
  
  request.onload = function() {
    poemDisplay.textContent = request.response;
  };
  
  request.send();
}
function turn_off() {
  const url = 'http://192.168.0.104/off';
  Http.open("GET", url);
  Http.send();
  // Http.onreadystatechange = (e) => {
  //   console.log(Http.responseText)
  // }
}