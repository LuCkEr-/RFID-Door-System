<?php

namespace KAC\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class RegisterAdminController extends Controller
{
    public function index ()
    {
        $users = DB::table('users')
        -> select('name', 'email')
        -> get();

        if (!count($users)) {

        }
        return view('auth.register', ['title' => 'Registreeri administraator konto']);
    }
}
