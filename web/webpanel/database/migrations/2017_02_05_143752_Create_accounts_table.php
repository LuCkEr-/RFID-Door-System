<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateAccountsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('accounts', function (Blueprint $table) {
            $table -> increments('userID');
            $table -> boolean('active');

            $table -> string('firstName');
            $table -> string('lastName');
            $table -> string('extraName');
            $table -> string('email');

            $table -> string('personalCode');

            $table -> string('homeAddress');
            $table -> string('workAddress');

            $table -> string('homePhone');
            $table -> string('mobilePhone');

            $table -> string('jobTitle');
            $table -> string('employer');
            $table -> text('comments');

            $table -> string('pan'); // ???
            $table -> string('businessName'); // ???

            $table -> primary('userID');

            $table -> timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::drop('accounts');
    }
}
