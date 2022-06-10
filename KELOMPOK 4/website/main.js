setInterval(function() {
    fetch("https://lampupintar.herokuapp.com/api")
        .then((hasil) => hasil.json())
        .then((res) => {
            console.log(res);
            document.getElementById("JAM").innerHTML = (res.JAM).toString() + ":" + (res.MENIT).toString() + ":" + (res.DETIK).toString();
            document.getElementById("TANGGAL").innerHTML = (res.TANGGAL).toString() + "/" + (res.BULAN).toString() + "/" + (res.TAHUN).toString();
            if (res.lampu == 0){
                document.getElementById("lampu").innerHTML = "Mati";
            }else{
                document.getElementById("lampu").innerHTML = "Hidup";
            }

        });
}, 1000);