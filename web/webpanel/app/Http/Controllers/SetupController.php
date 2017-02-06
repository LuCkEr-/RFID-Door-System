<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;

class SetupController extends Controller
{
    public function __construct()
    {
        $this->middleware('setup');
    }

    public function Setup()
    {
        return view('auth.register', ['title' => 'Palun registreeri administraator kasutaja']);
    }
}
