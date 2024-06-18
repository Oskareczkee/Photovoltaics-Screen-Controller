#pragma once
#include <pgmspace.h>

const char user_interface[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Sunwindgen</title>

    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet"
        integrity="sha384-T3c6CoIi6uLrA9TneNEoa7RxnatzjcDSCmG1MXxSR1GAsXEV/Dwwykc2MPK8M2HN" crossorigin="anonymous">
</head>
<style>
    body {
        background-image: linear-gradient(43deg, #4158D0 0%, #C850C0 46%, #FFCC70 100%);
        background-color: rgba(0, 0, 0, 0.5);
        background-blend-mode: darken;
        min-height: 100vh;
        margin: 0;
        padding: 0;
        font-size: 16px;
    }

    @media screen and (max-width: 420px) {
        * {
            font-size: 10px;
        }
    }

    .blur {
        backdrop-filter: blur(20px);
    }

    .blur-background-black {
        background-color: rgba(0, 0, 0, 0.3);
    }

    .lds-dual-ring {
        display: inline-block;
        width: 32px;
        height: 32px;
    }

    .lds-dual-ring:after {
        content: " ";
        display: block;
        width: 32px;
        height: 32px;
        margin: 8px;
        border-radius: 50%;
        border: 3px solid #fff;
        border-color: #fff transparent #fff transparent;
        animation: lds-dual-ring 1.2s linear infinite;
    }

    @keyframes lds-dual-ring {
        0% {
            transform: rotate(0deg);
        }

        100% {
            transform: rotate(360deg);
        }
    }
</style>

<body>
    <nav class="px-4 navbar navbar-expand-lg navbar-dark blur blur-background-black 
            border-bottom border-3 border-white">
        <div class="container-fluid">
            <a class="navbar-brand" href="#">Sunwindgen</a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarNavAltMarkup"
                aria-controls="navbarNavAltMarkup" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse justify-content-between" id="navbarNavAltMarkup">
                <div class="navbar-nav">
                    <a class="nav-item nav-link active" href="#">Home</a>
                    <a class="nav-item nav-link" href="#">Devices</a>
                    <a class="nav-item nav-link" href="#">Details</a>
                    <a class="nav-item nav-link" href="#">Change Network</a>
                    <a class="nav-item nav-link" href="#">Privacy</a>
                </div>
                <div class="d-flex align-items-center">
                    <button class="btn btn-sm btn-success px-3" id="--button-login">Login</button>
                </div>

            </div>
        </div>
    </nav>
    <div class="vh-100 d-flex flex-column align-items-center justify-content-center" id="content">
        <h1 class="text-white text-center">Welcome to Sundwingen solar panel control system</h1>
        <h5 class="text-white text-center">Please login to your solar panel provider and start your journey!</h5>
    </div>

    <footer class="d-flex justify-content-center blur blur-background-black text-white text-center py-3">
        2023-2023 Sunwindgen, Created by: Oskar Niedźwiedzki
    </footer>

    <script src="https://code.jquery.com/jquery-3.7.1.min.js"
        integrity="sha256-/JqT3SQfawRcv/BIHPThkBvs0OEvtFFmqPF/lYI/Cxo=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.14.7/dist/umd/popper.min.js"
        integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1"
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/js/bootstrap.min.js"
        integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM"
        crossorigin="anonymous"></script>


    <!--To copy elements-->
    <div class="d-none" id="--user-logged-in">
        <span class="nav-item navbar-text">Logged in to
            <span class="text-white" id="--login-provider-name">Solarman</span>
            as
            <span class="text-white" id="--login-name">no@mail.com</span>
        </span>
    </div>

    <!--main script-->
    <script>
        $("#--button-login").on('click', function (e) {
            $.ajax({
                method: "GET",
                url: "/login",
                dataType: "html",
                success: (page) => $("#content").html(page),
                error: () => alert("Something went wrong with GET Request to login page, contact administrator")
            });
        });
    </script>


</body>

</html>
)rawliteral";

const char login_page[] PROGMEM = R"rawliteral(
<div class="h-100 w-100 d-flex flex-column 
justify-content-center align-items-center text-white">
    <h1 class="mb-5">Login to solar panel provider</h1>
    <form name="login-form" class="d-flex flex-column">

        <div class="d-flex gap-3 mb-4 align-items-center w-100">
            <input type="radio" class="btn-check" name="providers" id="provider-solarman" value="Solarman"
                autocomplete="off">
            <label class="btn btn-success" for="provider-solarman">Solarman</label>

            <input type="radio" class="btn-check" name="providers" id="option2" autocomplete="off">
            <label class="btn btn-success" for="option2">Other</label>

            <input type="radio" class="btn-check" name="providers" id="option3" autocomplete="off">
            <label class="btn btn-success" for="option3">Other</label>

            <input type="radio" class="btn-check" name="providers" id="option4" autocomplete="off">
            <label class="btn btn-success" for="option4">Other</label>
        </div>

        <div class="d-flex gap-3 mb-2 align-items-center w-100">
            <label class="form-label w-25 me-2 text-end" for="username">Username</label>
            <input class="form-control w-75" type="text" name="username" id="username">
        </div>
        <div class="d-flex gap-3 mb-2 align-items-center w-100">
            <label class="form-label w-25 me-2 text-end" for="password">Password</label>
            <input class="form-control w-75" type="password" name="clear_text_pwd" id="password" />
        </div>

        <input type="hidden" name="grant_type" value="mdc_password">
        <input type="hidden" name="identity_type" value="2">
        <input type="hidden" name="client_id" value="test">

        <div class="align-self-end d-flex align-items-center justify-content-center">
            <div class="lds-dual-ring d-none" id="loading"></div>
            <button class="btn btn-success" type="submit">Login</button>
        </div>
    </form>
</div>

<script type="text/javascript">
    
    const form = document.forms.namedItem("login-form");
    async function sha256(message) {
        const msgBuffer = new TextEncoder().encode(message);
        const hashBuffer = await crypto.subtle.digest('SHA-256', msgBuffer);
        const hashArray = Array.from(new Uint8Array(hashBuffer));

        const hashHex = hashArray.map(b => b.toString(16).padStart(2, '0')).join('');
        return hashHex;
    }

    form.addEventListener('submit', async function (event) {
        event.preventDefault();
        $("#loading").removeClass("d-none");

        var provider = $("input[type=radio][name=providers]:checked").val();
        var token;
        var error = false;
        const formData = new FormData(form);

        //login to provider and get token
        switch (provider) {
            case 'Solarman':
                {
                    $.ajax({
                        type: "POST",
                        url: "https://home.solarmanpv.com/mdc-eu/oauth-s/oauth/token",
                        async: false, //wait till token in available
                        dataType: "json",
                        data: {
                            grant_type: "mdc_password",
                            username: formData.get("username"),
                            clear_text_pwd: formData.get("clear_text_pwd"),
                            password: await sha256(formData.get("clear_text_pwd")),
                            identity_type: 2,
                            client_id: "test",
                        },
                        success: function (response) {
                            alert("Its ok");
                            token = response.access_token;
                        },
                        error: function(){
                            alert("Invalid username or password");
                            error=true;
                        }
                    });
                    break;
                }
            default:
                alert("Provider must be chosen!");
                $("#loading").addClass("d-none");
                return;
        }

        //there was error when processing something
        if (error === true) {
            $("#loading").addClass("d-none");
            return;
        }

        //pass token and provider to the esp for further use
        $.ajax({
            type: "POST",
            url: "/api-login",
            async: false,
            data: {
                "provider": provider,
                "access_token": token
            },
            success: (data) => alert("Everything went good"),
            error: () => alert("Whoopsie something went wrong")
        });

        $("#loading").addClass("d-none");
    });
</script>
)rawliteral";