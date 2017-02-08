<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class SetupController extends Controller
{
    public function Setup()
    {
        $users = DB::table('users')
        -> select('name', 'email')
        -> get();

        if (!count($users))
        {
            return view('auth.register', ['title' => 'Palun registreeri administraator kasutaja']);
        } else {
            return redirect('/login');
        }
    }
}
