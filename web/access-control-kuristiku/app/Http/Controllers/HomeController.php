<?php

namespace KAC\Http\Controllers;

use Illuminate\Http\Request;

class HomeController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        //$this->middleware('auth');
    }

    public function accounts()
    {
        //$users = KAC\User::all();
        //return view('pages.accounts', ['users' => $users]);
    }

    public function cards()
    {
        //$cards = KAC\rfidCards::all();
        //return view('pages.cards', ['cards' => $cards]);
    }

    public function userSettings()
    {
        //$user = DB::table('users')
        //-> select('name', 'email')
        //-> where('email', Auth::user() -> email)
        //-> limit(1)
        //-> get();
        //return view('pages.userSettings', ['user' => $user]);
    }
}
