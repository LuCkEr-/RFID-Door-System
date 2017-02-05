<?php

namespace KAC\Http\Controllers;

use Illuminate\Http\Request;

class InitSetupController extends Controller
{
    public function index ()
    {
        return view('auth.register', ['title' => 'Registreeri administraator konto']);
    }
}
